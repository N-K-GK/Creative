#include "Result.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "Furniture.h"
#include "Room_layout.h"

const char* S_normal_coment[] = {"素晴らしい！私の希望をとても叶えてくれました！", 
                                 "想像していた以上の部屋です！とても気に入りました！",
                                 "完璧な提案です！あなたにお願いして本当に良かったです！"};
const char* A_normal_coment[] = {"素晴らしい部屋です！希望も反映されていて、とても満足です！",
                                 "全体のバランスが良いですね。ぜひこの部屋で暮らしてみたいです！",
                                 "期待以上の仕上がりです！細かいところまで考えられていますね！"};
const char* B_normal_coment[] = {"全体的によくまとまっています。なかなか良い部屋ですね！",
                                 "希望もしっかり反映されています。快適に過ごせそうです！",
                                 "もう少しこだわりがあると、さらに良くなりそうです。"};
const char* C_normal_coment[] = {"悪くはないですが、もう少し希望を反映してほしかったです。",
                                 "悪くはないですが、少し物足りなさを感じます。",
                                 "良いところもありますが、もう一歩工夫があると嬉しいですね。"};
const char* D_normal_coment[] = {"希望と違う部分もありますが、これからの成長に期待しています。",
                                 "もう少し工夫すると、より良い部屋になりそうですね。",
                                 "今回は少し残念な結果でしたが、次の提案も楽しみにしています。"};

const char* S_good_coment[] = {"最高の部屋です！！あなたに依頼して本当に良かったです！！",
                               "想像以上の仕上がりです！！また機会があれば、お願いしたいです！！",
                               "これ以上ないくらい理想通りです！！ありがとうございました！！"};
const char* A_good_coment[] = {"Sランクまであと少し！ほとんど完璧な仕上がりです！",
                               "本当に惜しいです！あと少しで最高評価でした！",
                               "ここまで完成度が高いとは思いませんでした。"};
const char* B_good_coment[] = {"あと少しでAランク！とても惜しいです！",
                               "あと少しの工夫でさらに上を目指せそうです！",
                               "ここまで来たらAランクを狙いたいですね！あと一歩です！"};
const char* C_good_coment[] = {"あと少しでBランク！かなり良いところまで来ています！", 
                               "もう少しだけ工夫できていれば、より高い評価になっていました！",
                               "あと一歩で、かなり満足できる部屋になりそうです！"};
const char* D_good_coment[] = {"あと少しで次のランクでした！もう一工夫あれば、より良くなりそうです。",
                               "かなり惜しい結果です！あと少し改善できれば、評価が上がりそうですね。",
                               "もう少しでもっと良くなるかも？次回に期待しています！"};

const char* bad_coment[] = {"正直、この部屋に住みたいとは思えません……。",
                            "申し訳ありませんが、今回の提案にはかなりがっかりしました…。",
                            "私の希望がほとんど反映されていないように感じます。"};

Result::Result()
{
    resultBackground = LoadTexture("assets/images/result_gazou.png");

    questNumber = 0;

    // 現段階では仮の評価
    score = 0;
    rank = "D";
    haiti = 0;
    kosei = 0;
    sum_kagu = 0;
    sum_cost = 0;
    cost = 0;

    // コメント未選択
    for(int i = 0; i < 8; i++){
        questComentNum[i] = 0;
        comentSelected[i] = false;
    }

    // 次へボタン
    nextButton = {900, 0, 170, 50};
    // 家具詳細ボタン
    furnitureDetailsBtn = {10, 550, 100, 50};
    furnitureDetails = {130, 450, 250, 360};
    opencheck = 0;
    
}

//==================================================
// 依頼番号設定
//==================================================
void Result::SetQuest(int quest)
{
    questNumber = quest;

    // 現段階では固定
    score = 0;
    rank = "D";
    haiti = 0;
    kosei = 0;
    sum_kagu = 0;
    sum_cost = 0;
    cost = 0;

    //==================================================
    // この依頼のコメントがまだ決まっていない場合だけ選ぶ
    //==================================================
    if(!comentSelected[questNumber]){
        questComentNum[questNumber] = rand() % 3;

        comentSelected[questNumber] = true;
    }
}


//==================================================
// 更新
//==================================================
int Result::Update()
{
    if(CheckCollisionPointRec(GetMousePosition(), nextButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        opencheck = 0;
        if (questNumber + 1 == 8){
            return 2;
        }else{
            return 1;
        }
    }

    return 0;
}


//==================================================
// 描画
//==================================================
void Result::Draw(Font font)
{
    // 背景
    DrawTexturePro(resultBackground,{0,0,(float)resultBackground.width,(float)resultBackground.height},{0,0,1100,950},{0,0},0,WHITE);

    //==================================================
    // タイトル
    //==================================================
    DrawTextEx(
        font,
        TextFormat("0%d", questNumber + 1),
        {650, 0},
        50,
        2,
        BLACK
    );

    //==================================================
    // ★
    //==================================================
    if(strcmp(rank, "S") == 0){
        DrawTextEx(
            font,
            TextFormat("★★★★★"),
            {890, 100},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "A") == 0){
        DrawTextEx(
            font,
            TextFormat("★★★★☆"),
            {890, 100},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "B") == 0){
        DrawTextEx(
            font,
            TextFormat("★★★☆☆"),
            {890, 100},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "C") == 0){
        DrawTextEx(
            font,
            TextFormat("★★☆☆☆"),
            {890, 100},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "D") == 0){
        DrawTextEx(
            font,
            TextFormat("★☆☆☆☆"),
            {890, 100},
            50,
            2,
            BLACK
        );
    }

    //==================================================
    // 評価点
    //==================================================
    DrawTextEx(
        font,
        TextFormat("%d点", score),
        {900, 150},
        50,
        2,
        BLACK
    );

    //==================================================
    // ランク
    //==================================================
    if(strcmp(rank, "S") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {960, 200},
            70,
            2,
            YELLOW
        );
    }else if(strcmp(rank, "A") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {960, 200},
            70,
            2,
            RED
        );
    }else if(strcmp(rank, "B") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {960, 200},
            70,
            2,
            BLUE
        );
    }else if(strcmp(rank, "C") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {960, 200},
            70,
            2,
            GREEN
        );
    }else if(strcmp(rank, "D") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {960, 200},
            70,
            2,
            BLACK
        );
    }

    //==================================================
    // 配置家具数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("配置家具数"),
        {10, 50},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d個", haiti),
        {10, 90},
        40,
        2,
        BLACK
    );

    //==================================================
    // 個性的家具数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("個性的家具数"),
        {10, 150},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d個", kosei),
        {10, 190},
        40,
        2,
        BLACK
    );

    //==================================================
    // 配置家具種類数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("配置家具種類数"),
        {10, 250},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d種類", sum_kagu),
        {10, 290},
        40,
        2,
        BLACK
    );

    //==================================================
    // 配置コスト
    //==================================================
    DrawTextEx(
        font,
        TextFormat("配置コスト"),
        {10, 350},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("￥%d / ￥%d", sum_cost, cost),
        {10, 390},
        40,
        2,
        BLACK
    );

    //==================================================
    // 解放要素
    //==================================================
    DrawTextEx(
        font,
        TextFormat("【色】"),
        {5, 640},
        40,
        2,
        BLACK
    );

    if(questNumber + 1 == 1){
        DrawTextEx(
            font,
            TextFormat("灰色"),
            {15, 680},
            40,
            2,
            BLACK
        );
    }else if(questNumber + 1 == 2){
        DrawTextEx(
            font,
            TextFormat("オレンジ・水色"),
            {15, 680},
            40,
            2,
            BLACK
        );
    }else if(questNumber + 1 == 3){
        DrawTextEx(
            font,
            TextFormat("カラフル・黄緑"),
            {15, 680},
            40,
            2,
            BLACK
        );
    }else if(questNumber + 1 == 4){
        DrawTextEx(
            font,
            TextFormat("金・銀・銅"),
            {15, 680},
            40,
            2,
            BLACK
        );
    }

    DrawTextEx(
        font,
        TextFormat("【その他】"),
        {5, 730},
        40,
        2,
        BLACK
    );

    if(questNumber + 1 == 3){
        DrawTextEx(
            font,
            TextFormat("追加情報"),
            {15, 770},
            40,
            2,
            BLACK
        );
    }else if(questNumber + 1 == 5){
        DrawTextEx(
            font,
            TextFormat("ヒアリング機能"),
            {15, 770},
            40,
            2,
            BLACK
        );
    }

    DrawTextEx(
        font,
        TextFormat("【家具】"),
        {5, 510},
        40,
        2,
        BLACK
    );

    if(questNumber + 1 <= 5){
        DrawRectangleRec(furnitureDetailsBtn, (Color){187, 255, 233, 255});
        DrawTextEx(font, "家具の詳細", {10, 550}, 25, 2, BLACK);
    }

    //==================================================
    // 家具の詳細ボタンをクリック
    //==================================================
    if(questNumber + 1 <= 5 && CheckCollisionPointRec(GetMousePosition(),furnitureDetailsBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        opencheck = 1 - opencheck;
    }

    //==================================================
    // 家具の詳細表示
    //==================================================
    if(opencheck == 1){
        DrawRectangleRec(furnitureDetails, (Color){187, 255, 233, 255});
        UnlockLevel unlockLevel = static_cast<UnlockLevel>(questNumber + 1);

        int drawY = 450;

        for(int i = 0; i < sizeof(FurnitureList) / sizeof(FurnitureList[0]); i++){
            if(FurnitureList[i].unlock == unlockLevel){
                DrawTextEx(
                    font,
                    FurnitureList[i].name,
                    {130, (float)drawY},
                    30,
                    2,
                    BLACK
                );

                drawY += 30;
            }
        }
    }

    //==================================================
    // コメント
    //==================================================
    const char* coment = "";

    if(score < 0){
        coment = bad_coment[questComentNum[questNumber]];
    }else if(strcmp(rank, "S") == 0){
        coment = S_normal_coment[questComentNum[questNumber]];
    }else if(strcmp(rank, "A") == 0){
        coment = A_normal_coment[questComentNum[questNumber]];
    }else if(strcmp(rank, "B") == 0){
        coment = B_normal_coment[questComentNum[questNumber]];
    }else if(strcmp(rank, "C") == 0){
        coment = C_normal_coment[questComentNum[questNumber]];
    }else{
        coment = D_normal_coment[questComentNum[questNumber]];
    }

    DrawTextEx(
        font,
        coment,
        {170, 885},
        40,
        2,
        BLACK
    );

    //==================================================
    // 次へボタン
    //==================================================
    if(questNumber + 1 == 8){
        DrawRectangleRec(nextButton, YELLOW);
        DrawTextEx(
            font,
            "最終リザルトへ",
            {900, 0},
            30,
            2,
            BLACK
        );
    }else{
        DrawRectangleRec(nextButton, LIGHTGRAY);
        DrawTextEx(
            font,
            "依頼リストへ",
            {900, 0},
            30,
            2,
            BLACK
        );
    }
}