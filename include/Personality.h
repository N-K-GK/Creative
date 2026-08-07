#pragma once
#include "raylib.h"

enum class Personality{
    Calm,
    Cheerul,
    Active,
    Serious,
    Fashionable,
    loose,
    Methodical,
    Minimalist,
    Unique,
    Trendy,
    Narcissist,

    Count
};


inline const char* PersonalityText[] ={
    "落ち着いている",
    "明るい",
    "活発",
    "真面目",
    "おしゃれ好き",
    "面倒くさがり",
    "几帳面",
    "シンプル好き",
    "個性的",
    "流行好き",
    "ナルシスト"
};


inline const char* GetPersonalityText(Personality Personality){
    int index = (int)Personality;

    if(index < 0 || index >= (int)Personality::Count){
        return "";
    }

    return PersonalityText[index];
}


inline Personality RandomPersonality(){
    return static_cast<Personality>(GetRandomValue(0, (int)Personality::Count - 1));
}