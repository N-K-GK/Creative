#pragma once
#include "raylib.h"

class Room{

private:

    int exitflag = 0;
    Rectangle retireBtn;

    int room_quest[8] = {0};
    int score[8] = {0};

    Texture2D titleBackground;

    float request_colinterval = 50.0;

    Rectangle room_requestBtn[8];

    int quest_number = -1;

public:

    Room();

    void Update(int score[8]);
    void Draw(Font font);

    int Getquest_number() const;
    void ResetQuestNumber();
    int GetDifficulty();
};