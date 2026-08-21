#include "Room_quest.h"
#include <cstdio>
#include <random>

Room_quest::Room_quest(){


    SetWindowTitle("部屋レイアウト");



    titleBackground = LoadTexture("assets/images/room_gazou.png");

    memoTexture = LoadTexture("assets/images/list_gazou.png");


    questlistBtn = {30, 10, 130, 180};

    layoutBtn = {915, 20, 140, 60};



    for(int i = 0; i < 8; i++){

        requests[i].purpose = RandomPurpose();


        requests[i].personality = RandomPersonality();

        requests[i].age = RandomAge(requests[i].purpose);

        requests[i].favoritecolor = RandomFavoriteColor();

        requests[i].style = RandomStyle();

        requests[i].priority = RandomPriority(requests[i].age);

        requests[i].extra = RandomExtra(requests[i].age,requests[i].priority);

        requests[i].ng.condition = RandomNGCondition();


        switch(requests[i].ng.condition){

        case NGCondition::Not_color:

            requests[i].ng.ngColor =RandomNGColor(requests[i].favoritecolor);

            break;

        case NGCondition::Bit_small:

            requests[i].ng.smallFurniture =RandomSmallFurniture();

            break;

        default:
            break;
        }
        //確認用
        requests[i].room = RandomRoomData(i);
    }

}

void Room_quest::Update(){
    if(CheckCollisionPointRec(GetMousePosition(), questlistBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        bottan_number = -1;
    }

    if(CheckCollisionPointRec(GetMousePosition(), layoutBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        bottan_number = 1;
    }
}

void Room_quest::Draw(Font font){

    DrawTexturePro(titleBackground,{0,0,(float)titleBackground.width,(float)titleBackground.height},{0,0,1100,950},{0,0},0,WHITE);
    DrawRectangle(0,0,1100,950,Fade(BLACK,0.4f));

    DrawTexturePro(memoTexture,{0, 0, (float)memoTexture.width, (float)memoTexture.height},{questlistBtn.x, questlistBtn.y, questlistBtn.width, questlistBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "依頼リスト", {50, 50}, 25, 2, BLACK);

    DrawRectangleRec(layoutBtn, SKYBLUE);
    DrawTextEx(font, "レイアウト作成", {920, 30}, 25, 2, BLACK);

    CustomerRequest &request = requests[quest_number];

    if(quest_number == 0){
        DrawTextEx(font,TextFormat("依頼%d☆☆☆", quest_number + 1), {100, 200}, 50, 2, BLACK);
    }else if(quest_number >= 1 && quest_number <= 2){
        DrawTextEx(font,TextFormat("依頼%d★☆☆", quest_number + 1), {100, 200}, 50, 2, BLACK);
    }else if(quest_number >= 3 && quest_number <= 4){
        DrawTextEx(font,TextFormat("依頼%d★★☆", quest_number + 1), {100, 200}, 50, 2, BLACK);
    }else{
        DrawTextEx(font,TextFormat("依頼%d★★★", quest_number + 1), {100, 200}, 50, 2, BLACK);
    }

    DrawTextEx(font,TextFormat("お客様の情報"), {100, 240}, 50, 2, BLACK);

    DrawTextEx(font,(TextFormat("目的：%s",GetPurposeText(request.purpose))),{100, 320},60,2,BLACK);

    DrawTextEx(font,(TextFormat("性格：%s",GetPersonalityText(request.personality))),{100, 370},60,2,BLACK);

    DrawTextEx(font,(TextFormat("属性：%s",GetAgeText(request.age))),{100, 420},60,2,BLACK);

    DrawTextEx(font,(TextFormat("好きな色：%s",GetFavoriteColorText(request.favoritecolor))),{100, 470},60,2,BLACK);

    DrawTextEx(font,(TextFormat("希望のデザイン：%s",GetStyleText(request.style))),{100, 520},60,2,BLACK);

    DrawTextEx(font,(TextFormat("重要事項：%s",GetPriorityText(request.priority))),{100, 570},60,2,BLACK);

    if(quest_number >= 3){
        DrawTextEx(font,(TextFormat("追加条件：%s",GetExtraText(request.extra))),{100, 620},60,2,BLACK);
    }
    if (quest_number >= 5){
        DrawTextEx(font,TextFormat("NG条件：%s",GetNGRequestText(request.ng)),{100,670},60,2,BLACK);
    }

}

void Room_quest::SetQuest(int number){
    quest_number = number;
    bottan_number = 0;
}

int Room_quest::Getbottan_number() const{

    return bottan_number;
}

void Room_quest::ResetBottanNumber(){
    bottan_number = 0;
}

RoomData Room_quest::GetRoomData() const{

    return requests[quest_number].room;
}

Priority Room_quest::GetPriority(int index) const{

    return requests[index].priority;
}

Style Room_quest::GetStyle(int index) const{
    
    return requests[index].style;
}
