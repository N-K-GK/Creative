#pragma once

#include "raylib.h"

class Game_result
{
private:

    // 現在表示している依頼番号
    int questNumber;

    // クリア依頼数
    int sum_irai;
    int num_irai;

    // 評価点
    // 現段階では0点固定
    int score;
    int score_avr;
    int score_max;
    int score_min;

    // 家具数
    // 現段階では0個固定
    int haiti;
    int kosei;
    int sum_kagu;
    int sum_cost;
    int cost;

    // 評価ランク
    // 現段階ではD固定
    const char* rank;
    int num_s;
    int num_a;
    int num_b;
    int num_c;
    int num_d;

    // // 依頼ごとに選択したコメント番号
    // int questComentNum[8];

    // // 依頼ごとにコメントを選択済みか
    // bool comentSelected[8];

    // 次へボタン
    Rectangle nextButton;

    Texture2D lastresultBackground;

    // // 家具詳細ボタン
    // Rectangle furnitureDetailsBtn;
    // Rectangle furnitureDetails;
    // int opencheck = 0;

public:

    Game_result();

    // 依頼番号を設定
    void SetQuest(int quest);

    // 更新
    // 戻り値：
    // 0 = 何もなし
    // 1 = 次へ
    int Update();

    // 描画
    void Draw(Font font);
};