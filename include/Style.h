#pragma once
#include "raylib.h"

enum class Style{
    Japanese,
    Western,
    Nordic,
    Natural,
    Modern,
    Industrial,
    Gothic,
    Pop,
    Cute,
    Cool,
    Luxury,
    

    Count
};


inline const char* StyleText[] ={
    "和風",
    "洋風",
    "北欧風",
    "ナチュラル",
    "モダン",
    "インダストリアル",
    "ゴシック",
    "ポップ",
    "かわいい",
    "かっこいい",
    "高級感"
};


inline const char* GetStyleText(Style Style){
    int index = (int)Style;

    if(index < 0 || index >= (int)Style::Count){
        return "";
    }

    return StyleText[index];
}

inline Style RandomStyle(){
    return static_cast<Style>(GetRandomValue(0, (int)Style::Count - 1));
}