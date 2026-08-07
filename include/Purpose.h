#pragma once
#include "raylib.h"

enum class Purpose{
    RelaxAlone,
    RelaxFamily,
    PartyFriends,
    Lover,
    Hobby,
    WorkStudy,
    Photo,
    GuestRoom,

    Count
};


inline const char* PurposeText[] ={
    "一人でゆっくり過ごしたい",
    "家族でくつろぎたい",
    "友達を呼んで盛り上がりたい",
    "恋人との時間を楽しみたい",
    "趣味を楽しみたい",
    "仕事・勉強に集中したい",
    "おしゃれな写真を撮りたい",
    "来客用の部屋にしたい"
};


inline const char* GetPurposeText(Purpose purpose){
    int index = (int)purpose;

    if(index < 0 || index >= (int)Purpose::Count){
        return "";
    }

    return PurposeText[index];
}


inline Purpose RandomPurpose(){
    return static_cast<Purpose>(GetRandomValue(0, (int)Purpose::Count - 1));
}