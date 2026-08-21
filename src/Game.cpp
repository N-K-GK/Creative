#include "Game.h"
#include "TextManager.h"
#include <cstdio>

Game::Game(){



    scene = START;

    buildingBtn = {220, 335, 170, 170};
    lightingBtn = {420, 330, 170, 170};
    roomBtn = {650, 360, 170, 170};
    exitBtn  = {360, 750, 300, 60};

    titleBackground = LoadTexture("assets/images/title_gazou.png");


    LoadJapaneseFont();

}

void Game::LoadJapaneseFont(){

    // ゲーム内で使用する文字を全部まとめる
    const char* texts = TextManager::GetAllTexts();

    int count = 0;

    // UTF-8文字列 → Unicodeコードポイントへ変換
    int* codepoints = LoadCodepoints(texts, &count);

    jpFont = LoadFontEx("assets/fonts/NotoSansJP-Regular.ttf",32,codepoints,count);

    UnloadCodepoints(codepoints);

}

Game::~Game(){

    if(jpFont.texture.id > 0){
        UnloadFont(jpFont);
    }


    if(titleBackground.id > 0){
        UnloadTexture(titleBackground);
    }

}

void Game::Update(){

    switch(scene){

    case START:

        if(CheckCollisionPointRec(GetMousePosition(), buildingBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            scene = BUILDING;
        }

        if(CheckCollisionPointRec(GetMousePosition(), lightingBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            scene = LIGHTING;
        }

        if(CheckCollisionPointRec(GetMousePosition(), roomBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            scene = ROOM;
        }

        if(CheckCollisionPointRec(GetMousePosition(), exitBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            CloseWindow();
        }

        break;
    
    case BUILDING:

        break;
    
    case LIGHTING:

        

        break;

    case ROOM:

        
        room.Update(score);

        if(room.Getquest_number() != -1){
            quest_number = room.Getquest_number(); 
            room_quest.SetQuest(room.Getquest_number());
            room.ResetQuestNumber();
            scene = ROOM_QUEST;
        }

        if(room.GetDifficulty() != 0){
            room.ResetQuestNumber();
            scene = START;
        }
        
        

        break;

    case ROOM_QUEST:

        room_quest.Update();

        if(room_quest.Getbottan_number() == -1){
            room.ResetQuestNumber();
            scene = ROOM;
        }else if(room_quest.Getbottan_number() == 1){
            room_layout.SetQuest(room_quest.GetRoomData(),quest_number,room_quest.GetPriority(quest_number),room_quest.GetStyle(quest_number));
            room_quest.ResetBottanNumber();
            scene = ROOM_LAYOUT;
        }

        break;

    case ROOM_LAYOUT:

        room_layout.Update(jpFont);

        if(room_layout.Getbottan_number() == -1){
            room_layout.ResetBottanNumber();
            room_quest.ResetBottanNumber();
            Priority priority = room_quest.GetPriority(quest_number);
            Style style = room_quest.GetStyle(quest_number);
            room_layout.SetRequestData(priority, style);
            scene = ROOM_QUEST;
        }
        
        
        

        break;

    case RESULT:

        

        break;
    }
}

void Game::Draw(){

    switch(scene){

    case START:

        DrawTexturePro(titleBackground,{0,0,(float)titleBackground.width,(float)titleBackground.height},{0,0,1100,950},{0,0},0,WHITE);
        DrawRectangle(0,0,1100,950,Fade(BLACK,0.4f));

        DrawTextEx(jpFont, "クリエイティブディレクター", {340, 180}, 50, 2, WHITE);

        DrawRectangleRec(buildingBtn, BLANK);
        DrawTextEx(jpFont, "建築物&製品開発", {225, 410}, 28, 2, BLACK);

        DrawRectangleRec(lightingBtn, BLANK);
        DrawTextEx(jpFont, "ステージ演出", {440, 400}, 28, 2, BLACK);

        DrawRectangleRec(roomBtn, BLANK);
        DrawTextEx(jpFont, "部屋レイアウト", {670, 430}, 28, 2, BLACK);

        DrawRectangleRec(exitBtn, RED);
        DrawTextEx(jpFont, "EXIT", {480, 760}, 30, 2, BLACK);

        break;

    case BUILDING:

        //building.Draw(jpFont);

        break;

    case LIGHTING:

        //light.Draw(jpFont);

        break;

    case ROOM:

        room.Draw(jpFont);

        break;

    case ROOM_QUEST:

        room_quest.Draw(jpFont);

        break;

    case ROOM_LAYOUT:

        room_layout.Draw(jpFont);

        break;
    
    case RESULT:

        //result.Draw(jpFont);

        break;
    }
}

