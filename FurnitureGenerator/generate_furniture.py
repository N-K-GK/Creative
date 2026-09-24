import argparse
import base64
import json
import os
import re
from pathlib import Path


def load_config(path: Path):
    return json.loads(path.read_text(encoding="utf-8"))


def safe_name(text: str) -> str:
    text = re.sub(r"[\\/:*?\"<>|]", "_", text.strip())
    return text.replace(" ", "_")


def build_prompt(furniture_name, shape, material, color):
    return (
        f"A single {furniture_name}, {shape}. "
        f"This is a game asset for a furniture placement game. "
        f"Material: {material['prompt']}. Color/design: {color['prompt']}. "
        "Keep the exact same furniture category and basic shape; do not add extra objects. "
        "Three-quarter front view, centered, fully visible, realistic product render, "
        "clean silhouette, no person, no room, no floor, no wall, no text, "
        "transparent background, suitable as a 2D game asset."
    )


def make_jobs(furniture_name, shape, cfg):
    jobs = []
    for material in cfg["materials"]:
        for color in cfg["colors"]:
            filename = f"{safe_name(furniture_name)}_{material['key']}_{color['key']}.png"
            jobs.append({
                "furniture_name": furniture_name,
                "shape": shape,
                "material_key": material["key"],
                "material_name": material["name"],
                "color_key": color["key"],
                "color_name": color["name"],
                "filename": filename,
                "prompt": build_prompt(furniture_name, shape, material, color)
            })
    return jobs


def postprocess(src: Path, dst: Path, output_size: int):
    from PIL import Image

    img = Image.open(src).convert("RGBA")
    alpha = img.getchannel("A")
    bbox = alpha.getbbox()
    if bbox:
        img = img.crop(bbox)

    max_side = max(img.size)
    scale = (output_size * 0.9) / max_side if max_side else 1.0
    new_size = (max(1, int(img.width * scale)), max(1, int(img.height * scale)))
    img = img.resize(new_size, Image.Resampling.LANCZOS)

    canvas = Image.new("RGBA", (output_size, output_size), (0, 0, 0, 0))
    x = (output_size - img.width) // 2
    y = (output_size - img.height) // 2
    canvas.alpha_composite(img, (x, y))
    dst.parent.mkdir(parents=True, exist_ok=True)
    canvas.save(dst, "PNG")


def generate_one(client, job, temp_dir: Path, cfg):
    response = client.images.generate(
        model=cfg["image_model"],
        prompt=job["prompt"],
        size=cfg["image_size"],
        background="transparent",
        output_format="png",
        n=1,
    )
    data = response.data[0]
    if not getattr(data, "b64_json", None):
        raise RuntimeError("画像APIの応答にb64_jsonがありません。")
    raw = temp_dir / job["filename"]
    raw.write_bytes(base64.b64decode(data.b64_json))
    return raw


def main():
    parser = argparse.ArgumentParser(description="Creative Director furniture asset generator")
    parser.add_argument("--name", required=True, help="家具名（例: イス）")
    parser.add_argument("--shape", required=True, help="家具形状（例: 椅子（背もたれあり））")
    parser.add_argument("--config", default="config.json")
    parser.add_argument("--generate", action="store_true", help="画像生成APIまで実行")
    args = parser.parse_args()

    cfg = load_config(Path(args.config))
    jobs = make_jobs(args.name, args.shape, cfg)

    root = Path(cfg["project_root"]).resolve()
    asset_dir = root / cfg["asset_dir"]
    work_dir = Path("output") / safe_name(args.name)
    raw_dir = work_dir / "raw"
    raw_dir.mkdir(parents=True, exist_ok=True)

    (work_dir / "generation_plan.json").write_text(
        json.dumps({"furniture_name": args.name, "shape": args.shape, "jobs": jobs}, ensure_ascii=False, indent=2),
        encoding="utf-8"
    )

    print(f"生成予定: {len(jobs)}枚")
    for job in jobs:
        print(f"  - {job['material_name']} × {job['color_name']} -> {job['filename']}")

    if not args.generate:
        print("\n計画のみ作成しました。実際の画像生成には --generate を付けてください。")
        return

    if not os.environ.get("OPENAI_API_KEY"):
        raise SystemExit("OPENAI_API_KEY が設定されていません。")

    from openai import OpenAI
    client = OpenAI()

    processed = []
    for i, job in enumerate(jobs, 1):
        print(f"[{i}/{len(jobs)}] {job['material_name']} × {job['color_name']} を生成中...")
        raw = generate_one(client, job, raw_dir, cfg)
        dst = asset_dir / job["filename"]
        postprocess(raw, dst, int(cfg["output_size"]))
        processed.append(str(dst))
        print(f"  -> {dst}")

    (work_dir / "result.json").write_text(
        json.dumps({"files": processed}, ensure_ascii=False, indent=2),
        encoding="utf-8"
    )
    print("\n完了。既存のFurniture.hが参照しているファイル名に合わせれば、C++側のパス変更は不要です。")


if __name__ == "__main__":
    main()
