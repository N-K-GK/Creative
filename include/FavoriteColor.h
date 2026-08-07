#pragma once
#include "raylib.h"

enum class FavoriteColor{
    White,
    Black,
    Brown,
    Beige,
    Blue,
    Red,
    Green,
    Yellow,
    Pink,
    Purple,
    Warm_color,
    Cool_color,
    Monotone,

    Count
};


inline const char* FavoriteColorText[] ={
    "白",
    "黒",
    "茶色",
    "ベージュ",
    "青",
    "赤",
    "緑",
    "黄色",
    "ピンク",
    "紫",
    "暖色系",
    "寒色系",
    "モノトーン"
};


inline const char* GetFavoriteColorText(FavoriteColor FavoriteColor){
    int index = (int)FavoriteColor;

    if(index < 0 || index >= (int)FavoriteColor::Count){
        return "";
    }

    return FavoriteColorText[index];
}


inline FavoriteColor RandomFavoriteColor(){
    return static_cast<FavoriteColor>(GetRandomValue(0, (int)FavoriteColor::Count - 1));
}

inline bool IsSimilarColor(FavoriteColor favorite, FavoriteColor target){
    
    // 同じ色
    if(favorite == target){
        return true;
    }

    // ベージュと茶色
    if((favorite == FavoriteColor::Beige && target == FavoriteColor::Brown) || (favorite == FavoriteColor::Brown && target == FavoriteColor::Beige)){
        return true;
    }

    // モノトーン
    if(favorite == FavoriteColor::Monotone && (target == FavoriteColor::White || target == FavoriteColor::Black)){
        return true;
    }

    if(target == FavoriteColor::Monotone && (favorite == FavoriteColor::White || favorite == FavoriteColor::Black)){
        return true;
    }

    // 暖色系
    if(favorite == FavoriteColor::Warm_color && (target == FavoriteColor::Red || target == FavoriteColor::Yellow || target == FavoriteColor::Pink)){
        return true;
    }

    if(target == FavoriteColor::Warm_color && (favorite == FavoriteColor::Red || favorite == FavoriteColor::Yellow || favorite == FavoriteColor::Pink)){
        return true;
    }

    // 寒色系
    if(favorite == FavoriteColor::Cool_color && (target == FavoriteColor::Blue || target == FavoriteColor::Green || target == FavoriteColor::Purple)){
        return true;
    }

    if(target == FavoriteColor::Cool_color && (favorite == FavoriteColor::Blue || favorite == FavoriteColor::Green || favorite == FavoriteColor::Purple)){
        return true;
    }

    return false;
}

inline FavoriteColor RandomNGColor(FavoriteColor favorite){
    FavoriteColor result;

    do{
        result = static_cast<FavoriteColor>(GetRandomValue(0,(int)FavoriteColor::Count - 1));
    }while(IsSimilarColor(favorite, result));


    return result;
}