#pragma once
#include "raylib.h"
#include "Purpose.h"

enum class Age{
    Elementary_boy,
    Elementary_girl,
    Junior_boy,
    Junior_girl,
    High_boy,
    High_girl,
    University_boy,
    University_girl,
    Adult_boy,
    Adult_girl,
    Marriage,
    Family_boy,
    Family_girl,
    Senior_boy,
    Senior_girl,

    Count
};


inline const char* AgeText[] ={
    "小学生(男子)",
    "小学生(女子)",
    "中学生(男子)",
    "中学生(女子)",
    "高校生(男子)",
    "高校生(女子)",
    "大学生(男子)",
    "大学生(女子)",
    "社会人(男性)",
    "社会人(女性)",
    "新婚",
    "親子(男子)",
    "親子(女子)",
    "シニア(男性)",
    "シニア(女性)"
};


inline const char* GetAgeText(Age Age){
    int index = (int)Age;

    if(index < 0 || index >= (int)Age::Count){
        return "";
    }

    return AgeText[index];
}


inline Age RandomAge(Purpose purpose){
    while (true){
        Age age = static_cast<Age>(GetRandomValue(0, (int)Age::Count - 1));

        if(purpose == Purpose::RelaxAlone){
            if (age == Age::Marriage || age == Age::Family_boy || age == Age::Family_girl){
                continue;
            }
        }

        if(purpose == Purpose::GuestRoom){
            if(age == Age::Elementary_boy || age == Age::Elementary_girl || age == Age::Junior_boy || age == Age::Junior_girl || age == Age::High_boy || age == Age::High_girl){
                continue;
            }
        }

        return age;
    }
}