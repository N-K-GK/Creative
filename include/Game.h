#pragma once
#include "raylib.h"
#include "Room.h"
#include "Room_quest.h"
#include "Room_layout.h"
#include "Result.h"
#include "Game_result.h"
#include <string>

class Game{
private:

    enum Scene{
        START,
        BUILDING,
        LIGHTING,
        ROOM,
        ROOM_QUEST,
        ROOM_LAYOUT,
        RESULT,
        GAME_RESULT
    };

    Scene scene;

    Rectangle buildingBtn;
    Rectangle lightingBtn;
    Rectangle roomBtn;
    Rectangle exitBtn;

    Font jpFont;

    //Building building;
    //Lighting lighting;
    Room room;
    Room_quest room_quest;
    Room_layout room_layout;
    Result result;
    Game_result game_result;

    // 日本語フォント読み込み用
    void LoadJapaneseFont();

    // 背景画像
    Texture2D titleBackground;

    int score[8] = {0};

    int quest_number = 0;


public:

    Game();
    ~Game();

    void Update();
    void Draw();
};