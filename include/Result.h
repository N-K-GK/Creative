#pragma once

#include "raylib.h"

class Result
{
private:

    // 現在表示している依頼番号
    int questNumber;

    // 評価点
    // 現段階では0点固定
    int score;

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

    // 依頼ごとに選択したコメント番号
    int questComentNum[8];

    // 依頼ごとにコメントを選択済みか
    bool comentSelected[8];

    // 次へボタン
    Rectangle nextButton;

    Texture2D resultBackground;

public:

    Result();

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