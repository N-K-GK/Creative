#include "Game_result.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include "Furniture.h"


// const char* S_normal_coment[] = {"素晴らしい！私の希望をとても叶えてくれました！", 
//                                  "想像していた以上の部屋です！とても気に入りました！",
//                                  "完璧な提案です！あなたにお願いして本当に良かったです！"};
// const char* A_normal_coment[] = {"素晴らしい部屋です！希望も反映されていて、とても満足です！",
//                                  "全体のバランスが良いですね。ぜひこの部屋で暮らしてみたいです！",
//                                  "期待以上の仕上がりです！細かいところまで考えられていますね！"};
// const char* B_normal_coment[] = {"全体的によくまとまっています。なかなか良い部屋ですね！",
//                                  "希望もしっかり反映されています。快適に過ごせそうです！",
//                                  "もう少しこだわりがあると、さらに良くなりそうです。"};
// const char* C_normal_coment[] = {"悪くはないですが、もう少し希望を反映してほしかったです。",
//                                  "悪くはないですが、少し物足りなさを感じます。",
//                                  "良いところもありますが、もう一歩工夫があると嬉しいですね。"};
// const char* D_normal_coment[] = {"希望と違う部分もありますが、これからの成長に期待しています。",
//                                  "もう少し工夫すると、より良い部屋になりそうですね。",
//                                  "今回は少し残念な結果でしたが、次の提案も楽しみにしています。"};

// const char* S_good_coment[] = {"最高の部屋です！！あなたに依頼して本当に良かったです！！",
//                                "想像以上の仕上がりです！！また機会があれば、お願いしたいです！！",
//                                "これ以上ないくらい理想通りです！！ありがとうございました！！"};
// const char* A_good_coment[] = {"Sランクまであと少し！ほとんど完璧な仕上がりです！",
//                                "本当に惜しいです！あと少しで最高評価でした！",
//                                "ここまで完成度が高いとは思いませんでした。"};
// const char* B_good_coment[] = {"あと少しでAランク！とても惜しいです！",
//                                "あと少しの工夫でさらに上を目指せそうです！",
//                                "ここまで来たらAランクを狙いたいですね！あと一歩です！"};
// const char* C_good_coment[] = {"あと少しでBランク！かなり良いところまで来ています！", 
//                                "もう少しだけ工夫できていれば、より高い評価になっていました！",
//                                "あと一歩で、かなり満足できる部屋になりそうです！"};
// const char* D_good_coment[] = {"あと少しで次のランクでした！もう一工夫あれば、より良くなりそうです。",
//                                "かなり惜しい結果です！あと少し改善できれば、評価が上がりそうですね。",
//                                "もう少しでもっと良くなるかも？次回に期待しています！"};

// const char* bad_coment[] = {"正直、この部屋に住みたいとは思えません……。",
//                             "申し訳ありませんが、今回の提案にはかなりがっかりしました…。",
//                             "私の希望がほとんど反映されていないように感じます。"};

Game_result::Game_result()
{
    lastresultBackground = LoadTexture("assets/images/lastresult_gazou.png");

    //questNumber = 0;

    // 現段階では仮の評価
    score = 0;
    rank = "D";
    haiti = 0;
    kosei = 0;
    sum_kagu = 0;
    sum_cost = 0;
    cost = 0;

    sum_irai = 8;
    num_irai = 8;

    score_avr = 0;
    score_max = 0;
    score_min = 0;

    num_s = 0;
    num_a = 0;
    num_b = 0;
    num_c = 0;
    num_d = 0;

    // コメント未選択
    // for(int i = 0; i < 8; i++){
    //     questComentNum[i] = 0;
    //     comentSelected[i] = false;
    // }

    // 次へボタン
    nextButton = {800, 50, 200, 50};
    
}

//==================================================
// 依頼番号設定
//==================================================
void Game_result::SetQuest(int quest)
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

    sum_irai = 8;
    num_irai = 8;

    score_avr = 0;
    score_max = 0;
    score_min = 0;

    num_s = 0;
    num_a = 0;
    num_b = 0;
    num_c = 0;
    num_d = 0;

    //==================================================
    // この依頼のコメントがまだ決まっていない場合だけ選ぶ
    //==================================================
    // if(!comentSelected[questNumber]){
    //     questComentNum[questNumber] = rand() % 3;

    //     comentSelected[questNumber] = true;
    // }
}


//==================================================
// 更新
//==================================================
int Game_result::Update()
{
    if(CheckCollisionPointRec(GetMousePosition(), nextButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        return 1;
    }

    return 0;
}


//==================================================
// 描画
//==================================================
void Game_result::Draw(Font font)
{
    // 背景
    DrawTexturePro(lastresultBackground,{0,0,(float)lastresultBackground.width,(float)lastresultBackground.height},{0,0,1100,950},{0,0},0,WHITE);

    //==================================================
    // タイトル
    //==================================================
    DrawTextEx(
        font,
        TextFormat("ROOM DESIGN"),
        {200, 120},
        50,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("ALL CREAR"),
        {650, 110},
        70,
        2,
        YELLOW
    );

    //==================================================
    // クリア案件数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("%d / %d", num_irai, sum_irai),
        {510, 250},
        50,
        2,
        BLACK
    );

    //==================================================
    // 評価点表示
    //==================================================
    DrawTextEx(
        font,
        TextFormat("平均評価"),
        {350, 350},
        50,
        2,
        BLACK
    );
    DrawTextEx(
        font,
        TextFormat("%d点", score_avr),
        {650, 350},
        50,
        2,
        BLACK
    );
    DrawTextEx(
        font,
        TextFormat("最高評価"),
        {350, 400},
        50,
        2,
        BLACK
    );
    DrawTextEx(
        font,
        TextFormat("%d点", score_max),
        {650, 400},
        50,
        2,
        BLACK
    );
    DrawTextEx(
        font,
        TextFormat("最低評価"),
        {350, 450},
        50,
        2,
        BLACK
    );
    DrawTextEx(
        font,
        TextFormat("%d点", score_min),
        {650, 450},
        50,
        2,
        BLACK
    );

    //==================================================
    // 評価点
    //==================================================
    DrawTextEx(
        font,
        TextFormat("合計評価"),
        {350, 550},
        50,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d点", score),
        {650, 550},
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
            {450, 600},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "A") == 0){
        DrawTextEx(
            font,
            TextFormat("★★★★☆"),
            {450, 600},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "B") == 0){
        DrawTextEx(
            font,
            TextFormat("★★★☆☆"),
            {450, 600},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "C") == 0){
        DrawTextEx(
            font,
            TextFormat("★★☆☆☆"),
            {450, 600},
            50,
            2,
            BLACK
        );
    }else if(strcmp(rank, "D") == 0){
        DrawTextEx(
            font,
            TextFormat("★☆☆☆☆"),
            {450, 600},
            50,
            2,
            BLACK
        );
    }

    //==================================================
    // ランク
    //==================================================
    if(strcmp(rank, "S") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {520, 650},
            70,
            2,
            YELLOW
        );
    }else if(strcmp(rank, "A") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {520, 650},
            70,
            2,
            RED
        );
    }else if(strcmp(rank, "B") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {520, 650},
            70,
            2,
            BLUE
        );
    }else if(strcmp(rank, "C") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {520, 650},
            70,
            2,
            GREEN
        );
    }else if(strcmp(rank, "D") == 0){
        DrawTextEx(
            font,
            TextFormat("%s", rank),
            {520, 650},
            70,
            2,
            BLACK
        );
    }

    //==================================================
    // 各ランク取得数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("Sランク： %d", num_s),
        {750, 220},
        30,
        2,
        BLACK
    );
    
    DrawTextEx(
        font,
        TextFormat("Aランク： %d", num_a),
        {750, 250},
        30,
        2,
        BLACK
    );
    
    DrawTextEx(
        font,
        TextFormat("Bランク： %d", num_b),
        {750, 280},
        30,
        2,
        BLACK
    );
    
    DrawTextEx(
        font,
        TextFormat("Cランク： %d", num_c),
        {750, 310},
        30,
        2,
        BLACK
    );
    
    DrawTextEx(
        font,
        TextFormat("Dランク： %d", num_d),
        {750, 340},
        30,
        2,
        BLACK
    );

    //==================================================
    // 配置家具数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("総配置家具数"),
        {130, 800},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d個", haiti),
        {130, 840},
        40,
        2,
        BLACK
    );

    //==================================================
    // 個性的家具数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("総個性的家具数"),
        {330, 800},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d個", kosei),
        {330, 840},
        40,
        2,
        BLACK
    );

    //==================================================
    // 配置家具種類数
    //==================================================
    DrawTextEx(
        font,
        TextFormat("総配置家具種類数"),
        {560, 800},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("%d種類", sum_kagu),
        {560, 840},
        40,
        2,
        BLACK
    );

    //==================================================
    // 配置コスト
    //==================================================
    DrawTextEx(
        font,
        TextFormat("総配置コスト"),
        {810, 800},
        40,
        2,
        BLACK
    );

    DrawTextEx(
        font,
        TextFormat("￥%d", sum_cost),
        {810, 840},
        40,
        2,
        BLACK
    );

    //==================================================
    // コメント
    //==================================================
    // const char* coment = "";

    // if(score < 0){
    //     coment = bad_coment[questComentNum[questNumber]];
    // }else if(strcmp(rank, "S") == 0){
    //     coment = S_normal_coment[questComentNum[questNumber]];
    // }else if(strcmp(rank, "A") == 0){
    //     coment = A_normal_coment[questComentNum[questNumber]];
    // }else if(strcmp(rank, "B") == 0){
    //     coment = B_normal_coment[questComentNum[questNumber]];
    // }else if(strcmp(rank, "C") == 0){
    //     coment = C_normal_coment[questComentNum[questNumber]];
    // }else{
    //     coment = D_normal_coment[questComentNum[questNumber]];
    // }

    // DrawTextEx(
    //     font,
    //     coment,
    //     {170, 885},
    //     40,
    //     2,
    //     BLACK
    // );

    //==================================================
    // 次へボタン
    //==================================================
    DrawRectangleRec(nextButton, YELLOW);

    DrawTextEx(
        font,
        "ゲームモード選択へ",
        {800, 50},
        30,
        2,
        BLACK
    );
}