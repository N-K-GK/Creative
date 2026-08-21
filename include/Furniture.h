#pragma once
#include "raylib.h"

//家具データ
enum class FurnitureType
{
    //========================
    // 依頼1（初期から）
    //========================
    Chair,                  // イス
    Table,                  // テーブル
    Sofa,                   // ソファー
    Bed,                    // ベッド
    Bookshelf,              // 本棚
    Desk,                   // 机
    Television,             // テレビ
    Cabinet,                // 収納棚
    CeilingLight,           // シーリングライト

    //========================
    // 依頼1クリア
    //========================
    Laptop,                 // ノートパソコン
    Cage,                   // ケージ
    Piano,                  // ピアノ
    BarCounter,             // バーカウンター
    HandheldGame,           // 携帯ゲーム機
    Cushion,                // クッション
    DeskChair,              // デスクチェア
    WallClock,              // 壁掛け時計
    FloorLamp,              // スタンドライト
    TVStand,                // テレビ台
    Curtain,                // カーテン
    HousePlant,             // 観葉植物

    //========================
    // 依頼2クリア
    //========================
    Closet,                 // クローゼット
    DoubleBed,              // ダブルベッド
    CushionFloor,           // 座布団
    DisplayShelf,           // 飾り棚
    DiningTable,            // ダイニングテーブル
    DiningChair,            // ダイニングチェア
    Wallpaper,              // 壁紙
    Flooring,               // 床材
    PendantLight,           // ペンダントライト
    CornerSofa,             // L字ソファー
    KitchenCounter,         // キッチンカウンター
    Cupboard,               // 食器棚

    //========================
    // 依頼3クリア
    //========================
    VacuumCleaner,          // 掃除機
    WallShelf,              // 壁掛け棚
    FloorChair,             // 座椅子
    SideTable,              // サイドテーブル
    Carpet,                 // カーペット
    StorageCase,            // 引き出し収納ケース
    DesktopPC,              // デスクトップパソコン
    TableLamp,              // テーブルスタンド
    LowTable,               // ローテーブル
    Mirror,                 // 鏡
    ConsoleGame,            // 据え置きゲーム機
    Chandelier,             // シャンデリア

    //========================
    // 依頼4クリア
    //========================
    LargeBookshelf,         // 本棚（大型）
    CounterChair,           // カウンターチェア
    Painting,               // 絵画
    Candle,                 // キャンドル
    TrashCan,               // ゴミ箱
    DeskLamp,               // デスクスタンド
    Vase,                   // 花瓶
    Showcase,               // ショーケース
    Guitar,                 // ギター
    CatTower,               // キャットタワー
    PetToilet,              // ペットトイレ
    AirConditioner,         // エアコン

    //========================
    // 依頼5クリア
    //========================
    QueenBed,               // クイーンベッド
    GamingPC,               // ゲーミングPC
    Monitor,                // モニター
    GamingChair,            // ゲーミングチェア
    Speaker,                // スピーカー
    RecliningChair,         // リクライニングチェア
    RetroGameConsole,       // レトロゲーム機
    StuffedToy,             // ぬいぐるみ
    Clock,                  // 置き時計
    ElectricFan,            // 扇風機
    ShoeRack,               // 靴箱
    HangerRack,             // ハンガーラック

    Count
};

//========================
// 解放条件
//========================
enum class UnlockLevel
{
    Start,      // 初期
    Quest1,
    Quest2,
    Quest3,
    Quest4,
    Quest5
};

//========================
//分類
//========================
enum class FurnitureCategory
{
    All,          // 全家具表示用

    Furniture,    // 家具
    Storage,      // 収納
    Electronics,  // 家電
    Hobby,        // 趣味
    Lighting,     // 照明
    Decoration    // 装飾
    
};

//========================
// 色
//========================
enum class Colors
{
    White,
    Black,
    Red,
    Blue,
    Green,
    Yellow,
    Pink,
    Brown,
    Beige,
    Purple,

    Gray,

    Orange,
    Light_blue,

    Colorful,
    Yellow_green,

    Gold,
    Silver,
    Copper,

    Count
};

//========================
// 素材
//========================
enum class Materials
{
    Wood,
    Stone,
    Glass,
    Metal,
    Cloth,
    Leather,
    Rattan,
    Tile,

    Count
};

//========================
// 素材コスト
//========================
inline const int MaterialCost[] ={
    10, // Wood
    40, // Stone
    60, // Glass
    50, // Metal
    20, // Cloth
    90, // Leather
    30, // Rattan
    40  // Tile
};

//========================
// 家具情報
//========================
struct FurnitureData
{
    FurnitureType type;

    const char* name;

    //基本価格
    int baseCost;

    //解放条件
    UnlockLevel unlock;

    //分類
    FurnitureCategory category;

    //初期サイズ
    Vector2 size;

    // 画像ファイルのパス
    const char* texturePath;
    const char* colorfulTexturePath;

    Texture2D defaultTexture;
    Texture2D colorfulTexture;

    // デフォルト表示順
    int defaultOrder;
};

//========================
// 色情報
//========================
struct ColorData
{
    Colors type;

    const char* name;

    //解放条件
    UnlockLevel unlock;

    // デフォルト表示順
    int defaultOrder;
};

//========================
// 素材情報
//========================
struct MaterialData
{
    Materials type;

    const char* name;

    //基本価格
    int materialCost;

    // デフォルト表示順
    int defaultOrder;
};


//========================
// 家具一覧
//========================
inline FurnitureData FurnitureList[] =
{
//========================
// 初期家具
//========================
{FurnitureType::Chair, "イス", 20, UnlockLevel::Start, FurnitureCategory::Furniture, {80,80}, "assets/images/家具/イス.png", "assets/images/家具/イス_レインボー.png", {}, {}, 1},
{FurnitureType::Table, "テーブル", 50, UnlockLevel::Start, FurnitureCategory::Furniture,  {150,80}, nullptr, nullptr, {}, {}, 9},
{FurnitureType::Sofa, "ソファー", 100, UnlockLevel::Start, FurnitureCategory::Furniture,  {200,100}, nullptr, nullptr, {}, {}, 16},
{FurnitureType::Bed, "ベッド", 120, UnlockLevel::Start, FurnitureCategory::Furniture,  {200,150}, nullptr, nullptr, {}, {}, 18},
{FurnitureType::Bookshelf, "本棚", 60, UnlockLevel::Start, FurnitureCategory::Storage,  {100,180}, nullptr, nullptr, {}, {}, 24},
{FurnitureType::Desk, "机", 70, UnlockLevel::Start, FurnitureCategory::Furniture,  {140,80}, nullptr, nullptr, {}, {}, 8},
{FurnitureType::Television, "テレビ", 200, UnlockLevel::Start, FurnitureCategory::Electronics,  {120,80}, nullptr, nullptr, {}, {}, 36},
{FurnitureType::Cabinet, "収納棚", 150, UnlockLevel::Start, FurnitureCategory::Storage,  {120,180}, nullptr, nullptr, {}, {}, 23},
{FurnitureType::CeilingLight, "シーリングライト", 80, UnlockLevel::Start, FurnitureCategory::Lighting,  {100,100}, nullptr, nullptr, {}, {}, 50},

//========================
// 依頼1クリア
//========================
{FurnitureType::Laptop, "ノートパソコン", 250, UnlockLevel::Quest1, FurnitureCategory::Electronics,  {100,60}, nullptr, nullptr, {}, {}, 40},
{FurnitureType::Cage, "ケージ", 100, UnlockLevel::Quest1, FurnitureCategory::Decoration,  {120,120}, nullptr, nullptr, {}, {}, 70},
{FurnitureType::Piano, "ピアノ", 500, UnlockLevel::Quest1, FurnitureCategory::Hobby,  {220,120}, nullptr, nullptr, {}, {}, 48},
{FurnitureType::BarCounter, "バーカウンター", 700, UnlockLevel::Quest1, FurnitureCategory::Furniture,  {250,100}, nullptr, nullptr, {}, {}, 14},
{FurnitureType::HandheldGame, "携帯ゲーム機", 150, UnlockLevel::Quest1, FurnitureCategory::Hobby,  {80,50}, nullptr, nullptr, {}, {}, 45},
{FurnitureType::Cushion, "クッション", 30, UnlockLevel::Quest1, FurnitureCategory::Furniture,  {60,60}, nullptr, nullptr, {}, {}, 21},
{FurnitureType::DeskChair, "デスクチェア", 120, UnlockLevel::Quest1, FurnitureCategory::Furniture,  {80,100}, nullptr, nullptr, {}, {}, 2},
{FurnitureType::WallClock, "壁掛け時計", 50, UnlockLevel::Quest1, FurnitureCategory::Decoration,  {50,50}, nullptr, nullptr, {}, {}, 61},
{FurnitureType::FloorLamp, "スタンドライト", 100, UnlockLevel::Quest1, FurnitureCategory::Lighting,  {50,150}, nullptr, nullptr, {}, {}, 52},
{FurnitureType::TVStand, "テレビ台", 120, UnlockLevel::Quest1, FurnitureCategory::Furniture,  {150,60}, nullptr, nullptr, {}, {}, 13},
{FurnitureType::Curtain, "カーテン", 80, UnlockLevel::Quest1, FurnitureCategory::Decoration,  {200,150}, nullptr, nullptr, {}, {}, 56},
{FurnitureType::HousePlant, "観葉植物", 70, UnlockLevel::Quest1, FurnitureCategory::Decoration,  {80,120}, nullptr, nullptr, {}, {}, 64},

//========================
// 依頼2クリア
//========================
{FurnitureType::Closet, "クローゼット", 300, UnlockLevel::Quest2, FurnitureCategory::Storage,  {180,220}, nullptr, nullptr, {}, {}, 26},
{FurnitureType::DoubleBed, "ダブルベッド", 250, UnlockLevel::Quest2, FurnitureCategory::Furniture,  {250,170}, nullptr, nullptr, {}, {}, 19},
{FurnitureType::CushionFloor, "座布団", 20, UnlockLevel::Quest2, FurnitureCategory::Furniture,  {80,80}, nullptr, nullptr, {}, {}, 22},
{FurnitureType::DisplayShelf, "飾り棚", 150, UnlockLevel::Quest2, FurnitureCategory::Storage,  {120,180}, nullptr, nullptr, {}, {}, 27},
{FurnitureType::DiningTable, "ダイニングテーブル", 300, UnlockLevel::Quest2, FurnitureCategory::Furniture,  {220,120}, nullptr, nullptr, {}, {}, 10},
{FurnitureType::DiningChair, "ダイニングチェア", 100, UnlockLevel::Quest2, FurnitureCategory::Furniture,  {80,100}, nullptr, nullptr, {}, {}, 3},
{FurnitureType::Wallpaper, "壁紙", 200, UnlockLevel::Quest2, FurnitureCategory::Decoration,  {300,300}, nullptr, nullptr, {}, {}, 58},
{FurnitureType::Flooring, "床材", 250, UnlockLevel::Quest2, FurnitureCategory::Decoration,  {300,300}, nullptr, nullptr, {}, {}, 59},
{FurnitureType::PendantLight, "ペンダントライト", 180, UnlockLevel::Quest2, FurnitureCategory::Lighting,  {100,100}, nullptr, nullptr, {}, {}, 51},
{FurnitureType::CornerSofa, "L字ソファー", 350, UnlockLevel::Quest2, FurnitureCategory::Furniture,  {250,200}, nullptr, nullptr, {}, {}, 17},
{FurnitureType::KitchenCounter, "キッチンカウンター", 400, UnlockLevel::Quest2, FurnitureCategory::Furniture,  {250,100}, nullptr, nullptr, {}, {}, 15},
{FurnitureType::Cupboard, "食器棚", 250, UnlockLevel::Quest2, FurnitureCategory::Storage,  {150,220}, nullptr, nullptr, {}, {}, 28},

//========================
// 依頼3クリア
//========================
{FurnitureType::VacuumCleaner, "掃除機", 150, UnlockLevel::Quest3, FurnitureCategory::Furniture,  {80,120}, nullptr, nullptr, {}, {}, 38},
{FurnitureType::WallShelf, "壁掛け棚", 120, UnlockLevel::Quest3, FurnitureCategory::Storage,  {150,50}, nullptr, nullptr, {}, {}, 29},
{FurnitureType::FloorChair, "座椅子", 50, UnlockLevel::Quest3, FurnitureCategory::Furniture,  {100,80}, nullptr, nullptr, {}, {}, 6},
{FurnitureType::SideTable, "サイドテーブル", 80, UnlockLevel::Quest3, FurnitureCategory::Furniture,  {70,70}, nullptr, nullptr, {}, {}, 12},
{FurnitureType::Carpet, "カーペット", 100, UnlockLevel::Quest3, FurnitureCategory::Decoration,  {300,250}, nullptr, nullptr, {}, {}, 57},
{FurnitureType::StorageCase, "引き出し収納ケース", 130, UnlockLevel::Quest3, FurnitureCategory::Storage,  {120,100}, nullptr, nullptr, {}, {}, 30},
{FurnitureType::DesktopPC, "デスクトップパソコン", 500, UnlockLevel::Quest3, FurnitureCategory::Electronics,  {120,100}, nullptr, nullptr, {}, {}, 41},
{FurnitureType::TableLamp, "テーブルスタンド", 120, UnlockLevel::Quest3, FurnitureCategory::Lighting,  {50,80}, nullptr, nullptr, {}, {}, 53},
{FurnitureType::LowTable, "ローテーブル", 100, UnlockLevel::Quest3, FurnitureCategory::Furniture,  {180,80}, nullptr, nullptr, {}, {}, 11},
{FurnitureType::Mirror, "鏡", 80, UnlockLevel::Quest3, FurnitureCategory::Decoration,  {80,150}, nullptr, nullptr, {}, {}, 60},
{FurnitureType::ConsoleGame, "据え置きゲーム機", 300, UnlockLevel::Quest3, FurnitureCategory::Hobby,  {100,50}, nullptr, nullptr, {}, {}, 46},
{FurnitureType::Chandelier, "シャンデリア", 600, UnlockLevel::Quest3, FurnitureCategory::Lighting,  {150,150}, nullptr, nullptr, {}, {}, 55},

//========================
// 依頼4クリア
//========================
{FurnitureType::LargeBookshelf, "本棚（大型）", 400, UnlockLevel::Quest4, FurnitureCategory::Storage,  {200,250}, nullptr, nullptr, {}, {}, 25},
{FurnitureType::CounterChair, "カウンターチェア", 120, UnlockLevel::Quest4, FurnitureCategory::Furniture,  {70,120}, nullptr, nullptr, {}, {}, 4},
{FurnitureType::Painting, "絵画", 150, UnlockLevel::Quest4, FurnitureCategory::Decoration,  {100,100}, nullptr, nullptr, {}, {}, 63},
{FurnitureType::Candle, "キャンドル", 30, UnlockLevel::Quest4, FurnitureCategory::Decoration,  {30,50}, nullptr, nullptr, {}, {}, 66},
{FurnitureType::TrashCan, "ゴミ箱", 20, UnlockLevel::Quest4, FurnitureCategory::Storage,  {50,70}, nullptr, nullptr, {}, {}, 34},
{FurnitureType::DeskLamp, "デスクスタンド", 100, UnlockLevel::Quest4, FurnitureCategory::Lighting,  {50,80}, nullptr, nullptr, {}, {}, 54},
{FurnitureType::Vase, "花瓶", 50, UnlockLevel::Quest4, FurnitureCategory::Decoration,  {40,80}, nullptr, nullptr, {}, {}, 65},
{FurnitureType::Showcase, "ショーケース", 300, UnlockLevel::Quest4, FurnitureCategory::Storage,  {150,200}, nullptr, nullptr, {}, {}, 31},
{FurnitureType::Guitar, "ギター", 250, UnlockLevel::Quest4, FurnitureCategory::Hobby,  {80,180}, nullptr, nullptr, {}, {}, 49},
{FurnitureType::CatTower, "キャットタワー", 350, UnlockLevel::Quest4, FurnitureCategory::Decoration,  {100,250}, nullptr, nullptr, {}, {}, 68},
{FurnitureType::PetToilet, "ペットトイレ", 100, UnlockLevel::Quest4, FurnitureCategory::Decoration,  {100,80}, nullptr, nullptr, {}, {}, 69},
{FurnitureType::AirConditioner, "エアコン", 700, UnlockLevel::Quest4, FurnitureCategory::Electronics,  {150,80}, nullptr, nullptr, {}, {}, 37},

//========================
// 依頼5クリア
//========================
{FurnitureType::QueenBed, "クイーンベッド", 600, UnlockLevel::Quest5, FurnitureCategory::Furniture,  {300,180}, nullptr, nullptr, {}, {}, 20},
{FurnitureType::GamingPC, "ゲーミングPC", 800, UnlockLevel::Quest5, FurnitureCategory::Hobby,  {150,120}, nullptr, nullptr, {}, {}, 42},
{FurnitureType::Monitor, "モニター", 300, UnlockLevel::Quest5, FurnitureCategory::Hobby,  {120,80}, nullptr, nullptr, {}, {}, 43},
{FurnitureType::GamingChair, "ゲーミングチェア", 250, UnlockLevel::Quest5, FurnitureCategory::Furniture,  {100,130}, nullptr, nullptr, {}, {}, 7},
{FurnitureType::Speaker, "スピーカー", 150, UnlockLevel::Quest5, FurnitureCategory::Hobby,  {80,100}, nullptr, nullptr, {}, {}, 44},
{FurnitureType::RecliningChair, "リクライニングチェア", 300, UnlockLevel::Quest5, FurnitureCategory::Furniture,  {150,120}, nullptr, nullptr, {}, {}, 5},
{FurnitureType::RetroGameConsole, "レトロゲーム機", 200, UnlockLevel::Quest5, FurnitureCategory::Hobby,  {100,50}, nullptr, nullptr, {}, {}, 47},
{FurnitureType::StuffedToy, "ぬいぐるみ", 50, UnlockLevel::Quest5, FurnitureCategory::Decoration,  {70,70}, nullptr, nullptr, {}, {}, 67},
{FurnitureType::Clock, "置き時計", 50, UnlockLevel::Quest5, FurnitureCategory::Decoration,  {50,50}, nullptr, nullptr, {}, {}, 62},
{FurnitureType::ElectricFan, "扇風機", 100, UnlockLevel::Quest5, FurnitureCategory::Electronics,  {80,150}, nullptr, nullptr, {}, {}, 39},
{FurnitureType::ShoeRack, "靴箱", 100, UnlockLevel::Quest5, FurnitureCategory::Storage,  {150,150}, nullptr, nullptr, {}, {}, 32},
{FurnitureType::HangerRack, "ハンガーラック", 80, UnlockLevel::Quest5, FurnitureCategory::Storage,  {120,200}, nullptr, nullptr, {}, {}, 33}

};


//========================
// 色一覧
//========================
inline ColorData ColorList[] =
{
//========================
// 初期色
//========================
{Colors::White, "白", UnlockLevel::Start, 1},
{Colors::Black, "黒", UnlockLevel::Start, 2},
{Colors::Red, "赤", UnlockLevel::Start, 4},
{Colors::Blue, "青", UnlockLevel::Start, 11},
{Colors::Green, "緑", UnlockLevel::Start, 9},
{Colors::Yellow, "黄色", UnlockLevel::Start, 7},
{Colors::Pink, "ピンク", UnlockLevel::Start, 5},
{Colors::Brown, "茶色", UnlockLevel::Start, 13},
{Colors::Beige, "ベージュ", UnlockLevel::Start, 14},
{Colors::Purple, "紫", UnlockLevel::Start, 12},

//========================
// 依頼1クリア
//========================
{Colors::Gray, "灰色", UnlockLevel::Quest1, 3},

//========================
// 依頼2クリア
//========================
{Colors::Orange, "オレンジ", UnlockLevel::Quest2, 6},
{Colors::Light_blue, "水色", UnlockLevel::Quest2, 10},

//========================
// 依頼3クリア
//========================
{Colors::Colorful, "カラフル", UnlockLevel::Quest3, 15},
{Colors::Yellow_green, "黄緑", UnlockLevel::Quest3, 8},
//========================
// 依頼4クリア
//========================
{Colors::Gold, "金", UnlockLevel::Quest4, 16},
{Colors::Silver, "銀", UnlockLevel::Quest4, 17},
{Colors::Copper, "銅", UnlockLevel::Quest4, 18},

};

//========================
// 素材一覧
//========================
inline MaterialData MaterialList[] =
{
//========================
// 初期素材
//========================
{Materials::Wood, "木目調", 10, 1},
{Materials::Stone, "石目調", 40, 2},
{Materials::Glass, "ガラス", 60, 3},
{Materials::Metal, "金属", 50, 4},
{Materials::Cloth, "布", 20, 5},
{Materials::Leather, "レザー", 90, 6},
{Materials::Rattan, "ラタン", 30, 7},
{Materials::Tile, "タイル", 40, 8},

};


//========================
// 家具名取得
//========================
inline const char* GetFurnitureText(FurnitureType type)
{
    for(auto& furniture : FurnitureList){
        if(furniture.type == type){
            return furniture.name;
        }
    }

    return "";
}

// 小さめ家具をランダム取得
inline FurnitureType RandomSmallFurniture()
{
    return static_cast<FurnitureType>(GetRandomValue(0,(int)FurnitureType::Count - 1));
}



//========================
// 家具価格取得
//========================
inline int GetFurnitureCost(FurnitureType type)
{
    for(auto& furniture : FurnitureList){
        if(furniture.type == type){
            return furniture.baseCost;
        }
    }

    return 0;
}