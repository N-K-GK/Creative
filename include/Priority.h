#pragma once
#include <vector>
#include "raylib.h"
#include "Age.h"

enum class Priority{
    Cost,           // コスト重視
    Design,         // デザイン重視
    Comfort,        // 快適性重視
    Storage,        // 収納重視
    Safety,         // 安全性
    EasyMove,       // 動きやすさ重視
    Soundproof,     // 防音重視
    EasyClean,      // 掃除しやすさ重視

    Wide,           // 広く見せたい
    Luxury,         // 高級感重視
    Bright,         // 明るさ重視
    Functional,     // 機能性重視
    Unity,          // 統一感重視

    Count
};

inline const char* PriorityText[] ={
    "コスト重視",
    "デザイン重視",
    "快適性重視",
    "収納重視",
    "安全性",
    "動きやすさ重視",
    "防音重視",
    "掃除しやすさ重視",

    "広く見せたい",
    "高級感重視",
    "明るさ重視",
    "機能性重視",
    "統一感重視"
};

inline const char* GetPriorityText(Priority priority){
    int index = (int)priority;

    if(index < 0 || index >= (int)Priority::Count){
        return "";
    }

    return PriorityText[index];
}

inline const std::vector<Priority> PriorityTable[] ={
    // 小学生(男子)
    {
        Priority::Storage,
        Priority::Safety,
        Priority::Design,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 小学生(女子)
    {
        Priority::Storage,
        Priority::Safety,
        Priority::Design,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 中学生(男子)
    {
        Priority::Storage,
        Priority::Design,
        Priority::Cost,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 中学生(女子)
    {
        Priority::Storage,
        Priority::Design,
        Priority::Cost,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 高校生(男子)
    {
        Priority::Storage,
        Priority::Design,
        Priority::Cost,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 高校生(女子)
    {
        Priority::Storage,
        Priority::Design,
        Priority::Cost,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 大学生(男子)
    {
        Priority::Cost,
        Priority::Design,
        Priority::Comfort,
        Priority::Storage,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 大学生(女子)
    {
        Priority::Cost,
        Priority::Design,
        Priority::Comfort,
        Priority::Storage,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 社会人(男性)
    {
        Priority::Cost,
        Priority::Comfort,
        Priority::Soundproof,
        Priority::Design,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 社会人(女性)
    {
        Priority::Cost,
        Priority::Comfort,
        Priority::Soundproof,
        Priority::Design,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 新婚
    {
        Priority::Comfort,
        Priority::EasyMove,
        Priority::Design,
        Priority::EasyClean,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 親子(男子)
    {
        Priority::Safety,
        Priority::Storage,
        Priority::EasyClean,
        Priority::Soundproof,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // 親子(女子)
    {
        Priority::Safety,
        Priority::Storage,
        Priority::EasyClean,
        Priority::Soundproof,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // シニア(男性)
    {
        Priority::Safety,
        Priority::EasyMove,
        Priority::EasyClean,
        Priority::Comfort,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    },

    // シニア(女性)
    {
        Priority::Safety,
        Priority::EasyMove,
        Priority::EasyClean,
        Priority::Comfort,
        Priority::Wide,
        Priority::Luxury,
        Priority::Bright,
        Priority::Functional,
        Priority::Unity
    }
};

inline Priority RandomPriority(Age age){
    int index = (int)age;

    if(index < 0 || index >= (int)Age::Count){
        return Priority::Cost;
    }

    const auto& list = PriorityTable[index];

    return list[GetRandomValue(0, (int)list.size() - 1)];
}