#pragma once
#include "raylib.h"
#include "Age.h"
#include "Priority.h"

enum class Extra{
    Book_shelf,
    TV,
    Game,
    Piano,
    Pet,
    Desk_space,
    Collection,
    Bar,
    Houseplant,
    Indirect_lighting,
    

    Count
};


inline const char* ExtraText[] ={
    "本棚が欲しい",
    "テレビを置きたい",
    "ゲーム機を置きたい",
    "ピアノを置きたい",
    "ペットスペースが欲しい",
    "デスクスペースが欲しい",
    "コレクションを飾りたい",
    "バーカウンターが欲しい",
    "観葉植物を多めに置きたい",
    "間接照明を使いたい"
    
};


inline const char* GetExtraText(Extra Extra){
    int index = (int)Extra;

    if(index < 0 || index >= (int)Extra::Count){
        return "";
    }

    return ExtraText[index];
}


inline Extra RandomExtra(Age age, Priority priority){
    while (true){
        Extra extra = static_cast<Extra>(GetRandomValue(0, (int)Extra::Count - 1));

        if(priority == Priority::Cost){
            if (extra == Extra::Piano){
                continue;
            }
        }

        if(age == Age::Senior_boy || age == Age::Senior_girl){
            if (extra == Extra::Game){
                continue;
            }
        }

        if(age == Age::Elementary_boy || age == Age::Elementary_girl || age == Age::Junior_boy || age == Age::Junior_girl || age == Age::High_boy || age == Age::High_girl){
            if (extra == Extra::Bar){
                continue;
            }
        }

        return extra;
    }
}