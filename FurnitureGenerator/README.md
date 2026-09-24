# Creative Director 家具生成システム（試作）

Creative Director の家具画像制作で発生している定型作業を自動化するための試作です。

## この試作でできること

家具名と形状を指定すると、登録済みの「素材 × 色」の組み合わせを自動展開します。

例：

- イス × 木製 × 白色
- イス × 木製 × カラフル
- イス × 石目調 × 白色
- イス × 石目調 × カラフル
- ...

現在の Creative Director の `Furniture.h` にある8素材（木製、石目調、ガラス製、金属製、布製、レザー製、ラタン製、タイル調）と、白色・カラフルの2種類を初期設定にしています。

画像生成を実行すると、生成画像を透明PNG化し、1000×1000のキャンバスに統一して、`assets/images/家具/` に保存します。

## 重要

この試作では、既存の Creative Director が使用している画像ファイル名を利用する設計にしています。そのため、既存家具（例：イス）の画像を生成し直す場合は、対応する画像を置き換えるだけで、`Furniture.h` のパスを毎回変更する必要がありません。

## 使い方

Python 3.10以上を推奨。

```bash
pip install -r requirements.txt
```

まず生成予定だけ確認：

```bash
python generate_furniture.py --name "イス" --shape "椅子（背もたれあり）"
```

実際に画像生成まで行う場合：

```bash
export OPENAI_API_KEY="あなたのAPIキー"
python generate_furniture.py --name "イス" --shape "椅子（背もたれあり）" --generate
```

Windows PowerShellでは：

```powershell
$env:OPENAI_API_KEY="あなたのAPIキー"
python generate_furniture.py --name "イス" --shape "椅子（背もたれあり）" --generate
```

## 今後の拡張

1. GUIで家具名・形状・素材・色を入力
2. 生成する組み合わせをチェックボックスで選択
3. 生成前プレビュー
4. 生成進捗表示
5. 生成画像の確認・再生成
6. `Furniture.h` の新規家具登録まで自動化
7. Creative Director本体から家具生成システムを呼び出す
