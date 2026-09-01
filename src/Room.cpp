#include "Room.h"
#include <cstdio>

Room::Room(){

    SetWindowTitle("部屋レイアウト");

    titleBackground = LoadTexture("assets/images/room_gazou.png");

    retireBtn = {50, 10, 120, 60};

    request_colinterval = 100.0;
    for (int i = 0; i < 8; i++){
        room_requestBtn[i] = {100, 100 + (i * request_colinterval), 200, 50};
    }
}

void Room::Update(int score[8]){
    exitflag = 0;
    if(CheckCollisionPointRec(GetMousePosition(), retireBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        exitflag = 1;
    }

    room_quest[0] = 1; // 依頼1は最初から選択可能

    //確認用
    score[0] = 1;
    score[1] = 1;
    score[2] = 1;
    score[3] = 1;
    score[4] = 1;
    score[5] = 1;
    score[6] = 1;
    score[7] = 1;
    //

    for(int i = 1; i < 8; i++){
        if(score[i - 1] > 0){ //もし１つ前のスコアがあるなら
            room_quest[i] = 1; //依頼の受注可
        }else{
            room_quest[i] = 0; //依頼の受注不可
        }
    }

    for(int i = 0; i < 8; i++){
        if(room_quest[i] && CheckCollisionPointRec(GetMousePosition(), room_requestBtn[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            // scene切り替え
            quest_number = i;
        }
    }
}

void Room::Draw(Font font){

    DrawTexturePro(titleBackground,{0,0,(float)titleBackground.width,(float)titleBackground.height},{0,0,1100,950},{0,0},0,WHITE);
    DrawRectangle(0,0,1100,950,Fade(BLACK,0.4f));

    DrawRectangleRec(retireBtn, RED);
    DrawTextEx(font, "モード選択へ", {50, 18}, 25, 2, BLACK);

    DrawTextEx(font, "依頼リスト", {420, 20}, 70, 2, BLACK);

    for(int i = 0; i < 8; i++){
        if(room_quest[i]){ //もし依頼を受けることが出来るなら
            DrawRectangleRec(room_requestBtn[i], PURPLE);
        }else{
            DrawRectangleRec(room_requestBtn[i], GRAY);
        }

        if(i == 0){
            DrawTextEx(font,TextFormat("依頼%d☆☆☆", i + 1), {100, 100 + (i * request_colinterval)}, 50, 2, BLACK);
        }else if(i >= 1 && i <= 2){
            DrawTextEx(font,TextFormat("依頼%d★☆☆", i + 1), {100, 100 + (i * request_colinterval)}, 50, 2, BLACK);
        }else if(i >= 3 && i <= 4){
            DrawTextEx(font,TextFormat("依頼%d★★☆", i + 1), {100, 100 + (i * request_colinterval)}, 50, 2, BLACK);
        }else{
            DrawTextEx(font,TextFormat("依頼%d★★★", i + 1), {100, 100 + (i * request_colinterval)}, 50, 2, BLACK);
        }
    }
}

int Room::Getquest_number() const{

    return quest_number;
}

void Room::ResetQuestNumber(){
    quest_number = -1;
}

int Room::GetDifficulty(){

    return exitflag;

}
