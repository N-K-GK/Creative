#pragma once
#include "raylib.h"

/// 部屋の形
enum class RoomType
{
    Square,         // 正方形
    Vertical,       // 縦長
    Horizontal,     // 横長
    LShape,         // L字

    Count
};

/// ドアの位置
enum class DoorPosition
{
    BottomLeft,
    BottomRight,
    LeftBottom,
    RightMiddle,

    Count
};

/// 窓の位置
enum class WindowPosition
{
    Top,
    Left,
    Right,

    Count
};

/// 部屋サイズ
enum class RoomSize
{
    Medium,
    Large,

    Count
};

/// 部屋データ
struct RoomData
{
    RoomType roomType;

    RoomSize roomSize;

    DoorPosition door;

    WindowPosition windows[2];

    int windowCount;
};

//------------------------
// ランダム生成
//------------------------
inline RoomType RandomRoomType(){

    return static_cast<RoomType>(GetRandomValue(0,(int)RoomType::Count - 1));
}


inline RoomSize RandomRoomSize(){

    return static_cast<RoomSize>(GetRandomValue(0,(int)RoomSize::Count - 1));
}

// 部屋形状に合わせたドア生成
inline DoorPosition RandomDoorPosition(RoomType type){
    switch(type){

    // 正方形
    case RoomType::Square:

        return static_cast<DoorPosition>(GetRandomValue(0,1));

    // 縦長
    case RoomType::Vertical:

        return static_cast<DoorPosition>(GetRandomValue(0,1));

    // 横長
    case RoomType::Horizontal:

        return static_cast<DoorPosition>(0,1);

    // L字
    case RoomType::LShape:

        // 下側が欠ける想定なので左下固定
        return DoorPosition::LeftBottom;

    default:

        return DoorPosition::BottomLeft;
    }
}

// 部屋形状に合わせた窓生成
inline WindowPosition RandomWindow(RoomType type){

    switch(type){

    // 正方形
    case RoomType::Square:

        return static_cast<WindowPosition>(GetRandomValue(0,2));

    // 縦長
    case RoomType::Vertical:

        // 左右壁のみ
        return static_cast<WindowPosition>(GetRandomValue(1,2));

    // 横長
    case RoomType::Horizontal:

        // 上だけ
        return WindowPosition::Top;

    // L字
    case RoomType::LShape:

        // 欠けていない壁
        return WindowPosition::Top;

    default:

        return WindowPosition::Top;
    }
}

inline void RandomWindows(RoomData& room){
    // 横長・L字は窓1つ
    if(room.roomType == RoomType::Horizontal || room.roomType == RoomType::LShape){
        room.windowCount = 1;
        room.windows[0] = RandomWindow(room.roomType);
        return;
    }

    room.windowCount = GetRandomValue(1,2);

    room.windows[0] = RandomWindow(room.roomType);

    if(room.windowCount == 2){
        if(room.roomType == RoomType::Vertical){
            room.windows[1] = (room.windows[0] == WindowPosition::Left) ? WindowPosition::Right : WindowPosition::Left;
        }else{
            do{
                room.windows[1] = RandomWindow(room.roomType);
            } while(room.windows[0] == room.windows[1]);
        }
    }
}

//------------------------
// 部屋データ生成
//------------------------
inline RoomData RandomRoomData(int questNumber){
    RoomData room;

    // サイズ
    // 依頼1～5 → Medium
    if(questNumber < 5){
        room.roomSize = RoomSize::Medium;
    }else{ // 依頼6～8 → Large
        room.roomSize = RoomSize::Large;
    }

    // 依頼1は固定
    if(questNumber == 0){
        room.roomType = RoomType::Square;

        room.windowCount = 1;
        room.windows[0] = WindowPosition::Top;

        room.door = DoorPosition::BottomLeft;
    }else{
        // 部屋形状
        room.roomType = RandomRoomType();

        // 形状に合わせる
        room.door = RandomDoorPosition(room.roomType);

        RandomWindows(room);
    }

    return room;
}

//------------------------
// 表示文字
//------------------------
inline const char* RoomTypeText[] =
{
    "正方形",
    "縦長",
    "横長",
    "L字型"
};

inline const char* GetRoomTypeText(RoomType type){
    int index = (int)type;

    if(index < 0 || index >= (int)RoomType::Count){
        return "";
    }

    return RoomTypeText[index];
}

inline const char* DoorPositionText[] =
{
    "左下",
    "右下"
};

inline const char* GetDoorPositionText(DoorPosition position){
    int index = (int)position;

    if(index < 0 || index >= (int)DoorPosition::Count){
        return "";
    }

    return DoorPositionText[index];
}

inline const char* WindowPositionText[] =
{
    "上",
    "左",
    "右"
};

inline const char* GetWindowPositionText(WindowPosition position){
    int index = (int)position;

    if(index < 0 || index >= (int)WindowPosition::Count){
        return "";
    }

    return WindowPositionText[index];
}