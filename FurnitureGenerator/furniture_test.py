import openai
import os

api_key = os.getenv("OPENAI_API_KEY")
if api_key:
    print("APIキーを取得できました")
else:
    print("APIキーを取得できませんでした")
client = openai.OpenAI(api_key = api_key)

print("家具名を入力してください：")
furniture = input("→ ")
print("")

print("形状を入力してください：")
style = input("→ ")
print("")

print("素材")
print("1 木目調")
print("2 石目調")
print("3 ガラス")
print("4 金属")
print("5 布")
print("6 レザー")
print("7 ラタン")
print("8 タイル")
print("")

print("素材(数字)を選択してください：")
material_dict = {1:"木目調",2:"石目調",3:"ガラス",4:"金属",5:"布",6:"レザー",7:"ラタン",8:"タイル",}
materials = []
for i in range(8):
    try:
        material = input("→ ")

        if material == "":
            break

        material = int(material)

        if material < 1 or material > 8:
            print("無効な数字です。1～8から選択してください。")
            continue

        material_name = material_dict[material]

        if material_name in materials:
            print("入力済みです。他の数字を入力してください。")
            continue

        materials.append(material_name)

    except ValueError:
        print("数字を入力してください。")
        continue

print("")

print("色")
print("1 白")
print("2 黒")
print("3 灰色")
print("4 赤")
print("5 ピンク")
print("6 オレンジ")
print("7 黄色")
print("8 黄緑")
print("9 緑")
print("10 水色")
print("11 青")
print("12 紫")
print("13 茶色")
print("14 ベージュ")
print("15 カラフル")
print("16 金")
print("17 銀")
print("18 銅")
print("")

print("色(数字)を選択してください：")
color_dict = {1:"白",2:"黒",3:"灰色",4:"赤",5:"ピンク",6:"オレンジ",7:"黄色",8:"黄緑",9:"緑",10:"水色",11:"青",12:"紫",13:"茶色",14:"ベージュ",15:"カラフル",16:"金",17:"銀",18:"銅"}
colors = []
for j in range(18):
    try:
        color = input("→ ")

        if color == "":
            break

        color = int(color)

        if color < 1 or color > 18:
            print("無効な数字です。1～18から選択してください。")
            continue

        color_name = color_dict[color]

        if color_name in colors:
            print("入力済みです。他の数字を入力してください。")
            continue

        colors.append(color_name)

    except ValueError:
        print("数字を入力してください。")
        continue

print("")

print("家具名：" + furniture)
print("形状：" + style)
for k in range(len(materials)):
    print("素材： " + materials[k])

for l in range(len(colors)):
    print("色： " + colors[l])

pairs = []
for material in materials:
    for color in colors:
        print("組み合わせ：" + material + " ✕ " + color)
        pairs.append([material, color])

print(pairs)

for pair in pairs:
    print("ペア：" + pair[0] + " ✕ " + pair[1])

for pair in pairs:
    print("家具名：" + furniture)
    print("形状：" + style)
    print("材質：" + pair[0])
    print("色：" + pair[1])
    print("")

    prompt = style + "の" + furniture + "を" + pair[0] + "の素材で、色は" + pair[1] + "。背景は透明で、向きは正面から見た状態の画像を生成して"
    print(prompt)
    print("")

result = client.images.generate(model="gpt-image-2", prompt=prompt)

print(result)