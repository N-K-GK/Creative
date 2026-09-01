#pragma once
#include "raylib.h"
#include <array>
#include "Purpose.h"
#include "Personality.h"
#include "Age.h"
#include "FavoriteColor.h"
#include "Style.h"
#include "Priority.h"
#include "Extra.h"
#include "Ngcondition.h"
#include "Floor_plan.h"

class Room_quest{

private:

    Texture2D titleBackground;

    Texture2D memoTexture;

    float request_colinterval = 50.0;

    Rectangle questlistBtn;

    Rectangle layoutBtn;

    struct CustomerRequest {
        Purpose purpose;          //①
        Personality personality;  //②
        Age age;                  //③
        FavoriteColor favoritecolor;      //④
        Style style;              //⑥
        Priority priority;        //⑦
        Extra extra;              //⑧
        NGCondition ngcondition;  //⑨
        NGRequest ng;

        RoomData room;
    };

    CustomerRequest requests[8];

    int quest_number = 0;

    int bottan_number = 0;

public:
    Room_quest();
    void Update();
    void Draw(Font font);

    void SetQuest(int number);

    int Getbottan_number() const;

    void ResetBottanNumber();

    RoomData GetRoomData() const;

    Priority GetPriority(int index) const;
    Style GetStyle(int index) const;
};