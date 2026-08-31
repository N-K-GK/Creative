#pragma once
#include "raylib.h"
#include <array>
#include <vector>
#include "Room.h"
#include "Floor_plan.h"
#include "Furniture.h"
#include "Room_quest.h"

class Room_layout{

private:

    Texture2D titleBackground;

    Rectangle questdetailBtn;

    Rectangle furniturelist;

    Rectangle setfurniture;

    Rectangle allfurnitureBtn;
    Texture2D all_list;
    bool all_list_open = false;

    Rectangle furnitureBtn;
    Texture2D furniture_list;
    bool furniture_list_open = false;

    Rectangle storageBtn;
    Texture2D storage_list;
    bool storage_list_open = false;

    Rectangle electronicsBtn;
    Texture2D electronics_list;
    bool electronics_list_open = false;

    Rectangle hobbyBtn;
    Texture2D hobby_list;
    bool hobby_list_open = false;

    Rectangle lightBtn;
    Texture2D light_list;
    bool light_list_open = false;

    Rectangle decorationBtn;
    Texture2D decoration_list;
    bool decoration_list_open = false;

    int bottan_number = 0;

    RoomData room;

    struct FloorPlan
    {
        float x;
        float y;

        float width;
        float height;
    };

    FloorPlan floorPlan;

    int gold = 0;

    int questNumber = 0;

    FurnitureType selectedFurniture = FurnitureType::Count; // 未選択

    FurnitureCategory currentCategory = FurnitureCategory::All;

    bool furnitureListVisible = false;

    //詳細設定系ボタン
    Rectangle furnitureSetting;
    Rectangle settingCancelBtn;
    Rectangle settingDecisionBtn;
    Rectangle settingColorBtn;
    Rectangle settingMaterialBtn;

    //各色選択ボタン
    Rectangle settingWhiteBtn;
    Rectangle settingBlackBtn;
    Rectangle settingRedBtn;
    Rectangle settingBlueBtn;
    Rectangle settingGreenBtn;
    Rectangle settingYellowBtn;
    Rectangle settingPinkBtn;
    Rectangle settingBrownBtn;
    Rectangle settingBeigeBtn;
    Rectangle settingPurpleBtn;
    Rectangle settingGrayBtn;
    Rectangle settingOrangeBtn;
    Rectangle settingLight_blueBtn;
    Rectangle settingColorfulBtn;
    Rectangle settingYellow_greenBtn;
    Rectangle settingGoldBtn;
    Rectangle settingSilverBtn;
    Rectangle settingCopperBtn;

    //各素材選択ボタン
    Rectangle settingWoodBtn;
    Rectangle settingStoneBtn;
    Rectangle settingGlassBtn;
    Rectangle settingMetalBtn;
    Rectangle settingClothBtn;
    Rectangle settingLeatherBtn;
    Rectangle settingRattanBtn;
    Rectangle settingTileBtn;

    bool furnitureSettingVisible = false;

    int columns;
    float startX;
    float startY;
    float colWidth;
    float rowHeight;

    bool colorSelectVisible = false;

    Colors selectedColor = Colors::Count;

    UnlockLevel currentLevel = UnlockLevel::Start;

    bool skipClick = false;

    // 素材選択画面表示
    bool materialSelectVisible = false;

    // 選択中の素材
    Materials selectedMaterial = Materials::Count;

    FurnitureType settingFurniture = FurnitureType::Count;
    Colors settingColor = Colors::Count;
    Materials settingMaterial = Materials::Count;

    struct PlacedFurniture
    {
        FurnitureType type;
        Vector2 position;
        Colors color;
        Materials material;
    };

    // 依頼ごとの配置家具
    std::vector<std::vector<PlacedFurniture>> placedFurniture;

    // 依頼ごとのGold
    std::vector<int> questGold;

    Room_quest* roomQuest;

    Priority currentPriority;
    Style currentStyle;

    Priority priority;
    Style style;


public:
    Room_layout();
    void CreateFloorPlan();

    void Update(Font font);

    void DrawFloor();

    void DrawRoom();

    void DrawSquareRoom();
    void DrawVerticalRoom();
    void DrawHorizontalRoom();
    void DrawLShapeRoom();

    void DrawWindow();
    void DrawDoor();

    void SetUnlockLevel(UnlockLevel level);

    void DrawColorSelect(Font font);

    Color GetRaylibColor(Colors color);

    void DrawMaterialSelect(Font font);

    Color GetMaterialColor(Materials material);

    void Draw(Font font);

    int GetFurnitureCost(const PlacedFurniture &furniture);

    int CalculateFurnitureCost();

    int GetMaxGold();

    void SetQuest(RoomData data, int number, Priority priority, Style style);

    int Getbottan_number() const;

    void ResetBottanNumber();

    void ResetSetting();

    void SetRequestData(Priority priority, Style style);
};

inline bool IsColorUnlocked(UnlockLevel currentLevel, UnlockLevel unlockLevel){
    return static_cast<int>(currentLevel) >= static_cast<int>(unlockLevel);
}