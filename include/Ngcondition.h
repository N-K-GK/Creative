#pragma once
#include "raylib.h"
#include "FavoriteColor.h"
#include "Furniture.h"


enum class NGCondition{
    Not_color,          // 色は苦手
    Bit_small,          // 家具は小さめ
    Not_dark,           // 部屋は暗くしたくない
    Aisle_wide,         // 通路は広く
    Not_tall,           // 背の高い家具はNG
    Not_frontwindow,    // 窓の前には家具はNG

    Count
};


// NG条件の詳細
struct NGRequest{

    NGCondition condition;

    FavoriteColor ngColor;          // 苦手な色
    FurnitureType smallFurniture;   // 小さくする家具
};


// NG条件の種類
inline const char* NGConditionText[] ={

    "色",
    "大きな",
    "暗い部屋",
    "狭い通路",
    "背の高い家具",
    "窓前の家具"
};


// NG条件名取得
inline const char* GetNGConditionText(NGCondition condition){

    int index = (int)condition;

    if(index < 0 || index >= (int)NGCondition::Count){
        return "";
    }

    return NGConditionText[index];
}


// ランダム生成
inline NGCondition RandomNGCondition(){

    return static_cast<NGCondition>(GetRandomValue(0,(int)NGCondition::Count - 1));
}


// NG条件の詳細表示
inline const char* GetNGRequestText(NGRequest ng){

    switch(ng.condition){

    case NGCondition::Not_color:

        return TextFormat("%s",GetFavoriteColorText(ng.ngColor));

    case NGCondition::Bit_small:

        return TextFormat("大きな%s",GetFurnitureText(ng.smallFurniture));

    case NGCondition::Not_dark:

        return "暗い部屋";

    case NGCondition::Aisle_wide:

        return "狭い通路";

    case NGCondition::Not_tall:

        return "背の高い家具";

    case NGCondition::Not_frontwindow:

        return "窓前の家具";

    default:

        return "";
    }
}