#include "Room_layout.h"
#include "Furniture.h"
#include <cstdio>
#include <random>
#include <vector>
#include <algorithm>

Room_layout::Room_layout(){
    SetWindowTitle("部屋レイアウト");

    titleBackground = LoadTexture("assets/images/room_gazou.png");

    all_list = LoadTexture("assets/images/kagurisuto_zennkagu.png");
    furniture_list = LoadTexture("assets/images/kagurisuto_kagu.png");
    storage_list = LoadTexture("assets/images/kagurisuto_syunou.png");
    electronics_list = LoadTexture("assets/images/kagurisuto_kaden.png");
    hobby_list = LoadTexture("assets/images/kagurisuto_syumi.png");
    light_list = LoadTexture("assets/images/kagurisuto_syoumei.png");
    decoration_list = LoadTexture("assets/images/kagurisuto_sousyoku.png");

    questdetailBtn = {30, 20, 130, 60};

    furniturelist = {30, 780, 1000, 150};

    setfurniture = {30, 350, 180, 250};

    allfurnitureBtn = {70, 820, 100, 100};
    furnitureBtn = {205, 820, 100, 100};
    storageBtn = {340, 820, 100, 100};
    electronicsBtn = {475, 820, 100, 100};
    hobbyBtn = {610, 820, 100, 100};
    lightBtn = {745, 820, 100, 100};
    decorationBtn = {880, 820, 100, 100};

    gold = 0;

    all_list_open = false;
    furniture_list_open = false;
    storage_list_open = false;
    electronics_list_open = false;
    hobby_list_open = false;
    light_list_open = false;
    decoration_list_open = false;

    columns = 4;

    startX = 220;
    startY = 120;

    colWidth = 210;
    rowHeight = 35;

    furnitureSetting = {200,100,650,600};
    settingCancelBtn = {200,100,80,60};
    settingDecisionBtn = {770,100,80,60};

    settingColorBtn = {200,530,80,60};
    settingMaterialBtn = {200,600,80,60};

    placedFurniture.resize(8);
    questGold.resize(8, 0);

    for(int i = 0; i < (int)FurnitureType::Count; i++){
        FurnitureData &data = FurnitureList[i];

        // 基本画像
        if(data.texturePath != nullptr){
            Image image = LoadImage(data.texturePath);

            // テクスチャ読み込み
            data.defaultTexture = LoadTextureFromImage(image);

            // 透明部分を除いた範囲を取得
            data.defaultBounds = GetImageAlphaBounds(image);

            UnloadImage(image);
        }

        // カラフル画像
        if(data.colorfulTexturePath != nullptr){
            Image image = LoadImage(data.colorfulTexturePath);

            data.colorfulTexture = LoadTextureFromImage(image);

            // 透明部分を除いた範囲
            data.colorfulBounds = GetImageAlphaBounds(image);

            UnloadImage(image);
        }

        //==================================================
        // 素材別画像
        //==================================================
        for(int j = 0; j < (int)Materials::Count; j++){
            // 通常の素材画像
            if(data.materialTexturePath[j] != nullptr){
                Image image = LoadImage(data.materialTexturePath[j]);

                data.materialTexture[j] = LoadTextureFromImage(image);

                // 透明部分を除いた範囲
                data.materialBounds[j] = GetImageAlphaBounds(image);

                UnloadImage(image);
            }

            // 素材 + カラフル画像
            if(data.materialcolorfulTexturePath[j] != nullptr){
                Image image = LoadImage(data.materialcolorfulTexturePath[j]);

                data.materialcolorfulTexture[j] = LoadTextureFromImage(image);

                // 透明部分を除いた範囲
                data.materialcolorfulBounds[j] = GetImageAlphaBounds(image);

                UnloadImage(image);
            }
        }
    }
}

void Room_layout::CreateFloorPlan(){
    float width = 600;
    float height = 600;

    if(room.roomSize == RoomSize::Large){
        width *= 1.15f;
        height *= 1.15f;
    }

    switch(room.roomType){

    case RoomType::Square:

        floorPlan.width = width;
        floorPlan.height = width;

        break;

    case RoomType::Vertical:

        floorPlan.width = width * 0.7f;
        floorPlan.height = height;

        break;

    case RoomType::Horizontal:

        floorPlan.width = width;
        floorPlan.height = height * 0.7f;

        break;

    case RoomType::LShape:

        floorPlan.width = width;
        floorPlan.height = height;

        break;
    }

    //-----------------
    // 中央配置
    //-----------------
    floorPlan.x = (GetScreenWidth() - floorPlan.width) / 2.0f;
    floorPlan.y = 50;
}

void Room_layout::DrawFloor(){
    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    switch(room.roomType){

    case RoomType::Square:

        DrawRectangle(x,y,width,width,WHITE);

        break;

    case RoomType::Vertical:
    case RoomType::Horizontal:

        DrawRectangle(x,y,width,height,WHITE);

        break;

    case RoomType::LShape:

        // 上側の長方形
        DrawRectangle(x,y,width,height * 0.5f,WHITE);

        // 左下側の長方形
        DrawRectangle(x,y + height * 0.5f,width * 0.6f,height * 0.5f,WHITE);

        break;
    }
}

void Room_layout::DrawRoom(){
    DrawFloor();

    switch(room.roomType){

    case RoomType::Square:
        DrawSquareRoom();
        break;

    case RoomType::Vertical:
        DrawVerticalRoom();
        break;

    case RoomType::Horizontal:
        DrawHorizontalRoom();
        break;

    case RoomType::LShape:
        DrawLShapeRoom();
        break;
    }
}

void Room_layout::DrawSquareRoom(){
    float x = floorPlan.x;
    float y = floorPlan.y;

    float size = floorPlan.width;

    float lineWidth = 5;

    // 上
    DrawLineEx({x,y},{x+size,y},lineWidth,BLACK);

    // 左
    DrawLineEx({x,y},{x,y+size},lineWidth,BLACK);

    // 右
    DrawLineEx({x+size,y},{x+size,y+size},lineWidth,BLACK);

    // 下（ドア開口）
    if(room.door == DoorPosition::BottomLeft){
        // 左側
        DrawLineEx({x,y+size},{x+50,y+size},lineWidth,BLACK);

        // 右側
        DrawLineEx({x+130,y+size},{x+size,y+size},lineWidth,BLACK);
    }else{
        // 左側
        DrawLineEx({x,y+size},{x+size-130,y+size},lineWidth,BLACK);

        // 右側
        DrawLineEx({x+size-50,y+size},{x+size,y+size},lineWidth,BLACK);
    }
}

void Room_layout::DrawVerticalRoom(){
    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    float lineWidth = 5;

    // 上
    DrawLineEx({x,y},{x+width,y},lineWidth,BLACK);

    // 左
    DrawLineEx({x,y},{x,y+height},lineWidth,BLACK);

    // 右
    DrawLineEx({x+width,y},{x+width,y+height},lineWidth,BLACK);

    // 下（ドア開口）
    if(room.door == DoorPosition::BottomLeft){
        DrawLineEx({x,y+height},{x+50,y+height},lineWidth,BLACK);

        DrawLineEx({x+130,y+height},{x+width,y+height},lineWidth,BLACK);
    }else{
        DrawLineEx({x,y+height},{x+width-130,y+height},lineWidth,BLACK);

        DrawLineEx({x+width-50,y+height},{x+width,y+height},lineWidth,BLACK);
    }
}

void Room_layout::DrawHorizontalRoom(){
    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    float lineWidth = 5;

    // 上
    DrawLineEx({x,y},{x+width,y},lineWidth,BLACK);

    // 左
    DrawLineEx({x,y},{x,y+height},lineWidth,BLACK);

    // 右
    DrawLineEx({x+width,y},{x+width,y+height},lineWidth,BLACK);

    // 下（ドア開口）
    if(room.door == DoorPosition::BottomLeft){
        DrawLineEx({x,y+height},{x+50,y+height},lineWidth,BLACK);

        DrawLineEx({x+130,y+height},{x+width,y+height},lineWidth,BLACK);
    }else{
        DrawLineEx({x,y+height},{x+width-130,y+height},lineWidth,BLACK);

        DrawLineEx({x+width-50,y+height},{x+width,y+height},lineWidth,BLACK);
    }
}

void Room_layout::DrawLShapeRoom(){

    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    float lineWidth = 5;

    DrawLineEx({x,y},{x+width,y},lineWidth,BLACK);

    DrawLineEx({x,y},{x,y+height},lineWidth,BLACK);

    DrawLineEx({x,y+height},{x+width*0.6f,y+height},lineWidth,BLACK);

    DrawLineEx({x+width*0.6f,y+height},{x+width*0.6f,y+height*0.5f},lineWidth,BLACK);

    DrawLineEx({x+width*0.6f,y+height*0.5f},{x+width,y+height*0.5f},lineWidth,BLACK);

    DrawLineEx({x+width,y+height*0.5f},{x+width,y},lineWidth,BLACK);
}

void Room_layout::DrawWindow(){
    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    for(int i=0;i<room.windowCount;i++){
        switch(room.windows[i]){

        // 上側窓
        case WindowPosition::Top:

            DrawLineEx({x+width*0.3f,y},{x+width*0.6f,y},8,SKYBLUE);

            break;

        // 左側窓
        case WindowPosition::Left:

            DrawLineEx({x,y+height*0.3f},{x,y+height*0.6f},8,SKYBLUE);

            break;

        // 右側窓
        case WindowPosition::Right:

            DrawLineEx({x+width,y+height*0.3f},{x+width,y+height*0.6f},8,SKYBLUE);

            break;

        }
    }
}

void Room_layout::DrawDoor(){
    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    switch(room.door){

    // 下左
    case DoorPosition::BottomLeft:

        DrawLineEx({x+50,y+height},{x+130,y+height},8,ORANGE);

        break;

    // 下右
    case DoorPosition::BottomRight:

        DrawLineEx({x+width-130,y+height},{x+width-50,y+height},8,ORANGE);

        break;

    // 左下（L字用）
    case DoorPosition::LeftBottom:

        DrawLineEx({x,y+height-130},{x,y+height-50},8,ORANGE);

        break;

    // 右中央
    case DoorPosition::RightMiddle:

        DrawLineEx({x+width,y+150},{x+width,y+230},8,ORANGE);

        break;
    }
}

void Room_layout::DrawColorSelect(Font font){

    if(skipClick){
        skipClick = false;
        return;
    }

    DrawRectangle(150, 100, 760, 600, (Color){187, 255, 233, 255});

    DrawTextEx(font, "色選択", {480, 120}, 40, 2, BLACK);

    //========================
    // 表示する色一覧を作成
    //========================
    std::vector<int> drawList;

    for(int i = 0; i < sizeof(ColorList) / sizeof(ColorList[0]); i++){

        ColorData &colorData = ColorList[i];

        // 未解放なら表示しない
        if((int)colorData.unlock > questNumber){
            continue;
        }

        drawList.push_back(i);
    }

    //========================
    // defaultOrder順に並び替え
    //========================
    std::sort(drawList.begin(),drawList.end(),[](int a, int b){return ColorList[a].defaultOrder < ColorList[b].defaultOrder;});

    //========================
    // 描画
    //========================
    for(int index = 0; index < (int)drawList.size(); index++){

        ColorData &colorData = ColorList[drawList[index]];

        int column = index % 4;
        int row = index / 4;

        float x = 180 + column * 180;
        float y = 180 + row * 90;

        Rectangle colorBtn = {x, y, 150, 60};

        if(colorData.type == Colors::Colorful){
            // レインボー表示
            float width = colorBtn.width / 6.0f;

            Color rainbow[] ={RED,ORANGE,YELLOW,GREEN,BLUE,PURPLE};

            for(int i = 0; i < 6; i++){
                DrawRectangle(colorBtn.x + width * i,colorBtn.y,width,colorBtn.height,rainbow[i]);
            }
        }else{
            DrawRectangleRec(colorBtn,GetRaylibColor(colorData.type));
        }

        // 背景と同化しやすい色だけ枠線
        if(colorData.type == Colors::White){
            DrawRectangleLinesEx(colorBtn, 1.0f, BLACK);
        }

        DrawTextEx(font,colorData.name,{x, y + 65},25,2,BLACK);

        if(CheckCollisionPointRec(GetMousePosition(), colorBtn) &&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            selectedColor = colorData.type;
            colorSelectVisible = false;
        }
    }
}

Color Room_layout::GetRaylibColor(Colors color){
    switch(color)
    {
        case Colors::White:
            return WHITE;

        case Colors::Black:
            //return BLACK;
            return Color{45, 45, 45, 255};

        case Colors::Red:
            return RED;

        case Colors::Blue:
            return BLUE;

        case Colors::Green:
            return LIME;

        case Colors::Yellow:
            return YELLOW;

        case Colors::Pink:
            return PINK;

        case Colors::Brown:
            return BROWN;

        case Colors::Beige:
            return BEIGE;

        case Colors::Purple:
            return PURPLE;

        case Colors::Gray:
            return GRAY;

        case Colors::Orange:
            return ORANGE;

        case Colors::Light_blue:
            return SKYBLUE;

        case Colors::Yellow_green:
            return GREEN;

        case Colors::Gold:
            return GOLD;

        case Colors::Silver:
            return Color{192,192,192,255};

        case Colors::Copper:
            return Color{184,115,51,255};

        case Colors::Colorful:
            return Color{255,100,255,255};

        default:
            return WHITE;
    }
}

void Room_layout::DrawMaterialSelect(Font font){

    if(skipClick){
        skipClick = false;
        return;
    }

    DrawRectangle(150, 100, 760, 600,(Color){187, 255, 233, 255});

    DrawTextEx(font,"素材選択",{480, 120},40,2,BLACK);

    //========================
    // 現在選択している家具
    //========================
    FurnitureData &data = FurnitureList[(int)selectedFurniture];

    //========================
    // 表示する素材一覧を作成
    //========================
    std::vector<int> drawList;

    for(int i = 0; i < (int)Materials::Count; i++){
        // この家具に素材画像が存在しない場合は表示しない
        if(data.materialTexturePath[i] == nullptr){
            continue;
        }

        drawList.push_back(i);
    }

    //========================
    // defaultOrder順に並び替え
    //========================
    std::sort(drawList.begin(),drawList.end(),[](int a, int b){return MaterialList[a].defaultOrder < MaterialList[b].defaultOrder;});

    //========================
    // 描画
    //========================
    for(int index = 0; index < (int)drawList.size(); index++){
        MaterialData &materialData = MaterialList[drawList[index]];

        int column = index % 4;
        int row = index / 4;

        float x = 180 + column * 180;
        float y = 180 + row * 90;

        Rectangle materialBtn = {x,y,150,60};

        // 素材ボタン色
        DrawRectangleRec(materialBtn,GetMaterialColor(materialData.type));

        DrawTextEx(font,materialData.name,{x, y + 65},25,2,BLACK);

        //========================
        // 素材選択
        //========================
        if(CheckCollisionPointRec(GetMousePosition(),materialBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            selectedMaterial = materialData.type;

            materialSelectVisible = false;
        }
    }
}

Color Room_layout::GetMaterialColor(Materials material){

    switch(material)
    {
        case Materials::Wood:
            return BROWN;

        case Materials::Stone:
            return GRAY;

        case Materials::Glass:
            return SKYBLUE;

        case Materials::Metal:
            return LIGHTGRAY;

        case Materials::Cloth:
            return BEIGE;

        case Materials::Leather:
            return DARKBROWN;

        case Materials::Rattan:
            return ORANGE;

        case Materials::Tile:
            return RED;

        default:
            return WHITE;
    }
}

void Room_layout::Update(Font font){
    //========================
    // 依頼内容ボタン
    //========================
    if(CheckCollisionPointRec(GetMousePosition(), questdetailBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        ResetSetting();

        furnitureSettingVisible = false;
        colorSelectVisible = false;
        materialSelectVisible = false;
        furnitureListVisible = false;

        bottan_number = -1;
    }

    if(furnitureSettingVisible && !colorSelectVisible && !materialSelectVisible){
        if(CheckCollisionPointRec(GetMousePosition(), settingCancelBtn) &&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            furnitureSettingVisible = false;
            selectedFurniture = FurnitureType::Count;
            selectedColor = Colors::Count;
            selectedMaterial = Materials::Count;
            return;
        }

        if(CheckCollisionPointRec(GetMousePosition(), settingDecisionBtn) &&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            // 色と素材が選択されている場合のみ確定
            if(selectedColor != Colors::Count && selectedMaterial != Materials::Count){
                settingColor = selectedColor;
                settingMaterial = selectedMaterial;

                furnitureSettingVisible = false;
                furnitureListVisible = false;

            }
            return;
        }

        // 色選択ボタン
        if(CheckCollisionPointRec(GetMousePosition(), settingColorBtn)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            colorSelectVisible = true;
            skipClick = true;
            return;
        }

        // 素材選択ボタン
        if(CheckCollisionPointRec(GetMousePosition(), settingMaterialBtn)&& IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            materialSelectVisible = true;
            skipClick = true;
            return;
        }
    }

    //========================
    // 家具カテゴリー選択
    //========================
    if(furnitureSettingVisible == false){
        if(CheckCollisionPointRec(GetMousePosition(), allfurnitureBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::All){
                // すでに家具リスト表示中なら閉じる
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; //リスト表示フラグON
                currentCategory = FurnitureCategory::All; //表示するカテゴリー設定
            }
        }else if(CheckCollisionPointRec(GetMousePosition(), furnitureBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::Furniture){
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; 
                currentCategory = FurnitureCategory::Furniture; 
            }
        }else if(CheckCollisionPointRec(GetMousePosition(), storageBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::Storage){
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; 
                currentCategory = FurnitureCategory::Storage; 
            }
        }else if(CheckCollisionPointRec(GetMousePosition(), electronicsBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::Electronics){
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; 
                currentCategory = FurnitureCategory::Electronics; 
            }
        }else if(CheckCollisionPointRec(GetMousePosition(), hobbyBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::Hobby){
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; 
                currentCategory = FurnitureCategory::Hobby; 
            }
        }else if(CheckCollisionPointRec(GetMousePosition(), lightBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::Lighting){
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; 
                currentCategory = FurnitureCategory::Lighting; 
            }
        }else if(CheckCollisionPointRec(GetMousePosition(), decorationBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            if(furnitureListVisible && currentCategory == FurnitureCategory::Decoration){
                furnitureListVisible = false;
            }else{
                furnitureListVisible = true; 
                currentCategory = FurnitureCategory::Decoration; 
            }
        }
    }

    //========================
    // 家具選択処理
    //========================
    if(furnitureListVisible && !furnitureSettingVisible){ //家具リストが表示されているときのみ
        //========================
        // 表示する家具一覧を作成
        //========================
        std::vector<int> drawList;

        for(int i = 0; i < (int)FurnitureType::Count; i++){

            FurnitureData &data = FurnitureList[i];

            // 解放条件
            if((int)data.unlock > questNumber){
                continue;
            }

            // カテゴリー
            if(currentCategory != FurnitureCategory::All &&data.category != currentCategory){
                continue;
            }

            drawList.push_back(i);
        }

        //========================
        // defaultOrder順に並び替え
        //========================
        std::sort(drawList.begin(), drawList.end(),[](int a, int b){return FurnitureList[a].defaultOrder <FurnitureList[b].defaultOrder;});

        //========================
        // クリック判定
        //========================
        for(int index = 0; index < (int)drawList.size(); index++){

            FurnitureData &data = FurnitureList[drawList[index]];

            int col = index % columns;
            int row = index / columns;

            Vector2 pos = {startX + col * colWidth,startY + row * rowHeight};

            Vector2 size = MeasureTextEx(font, data.name, 25, 2);

            Rectangle rect = {pos.x,pos.y,size.x,size.y};

            if(CheckCollisionPointRec(GetMousePosition(), rect) &&IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                if(selectedFurniture == data.type){
                    selectedFurniture = FurnitureType::Count; // 選択解除
                    furnitureSettingVisible = false;
                }else{
                    // 新しい家具を選択したので設定を初期化
                    selectedFurniture = FurnitureType::Count;
                    selectedColor = Colors::Count;
                    selectedMaterial = Materials::Count;

                    selectedFurniture = data.type; // 選択
                    furnitureSettingVisible = true;
                }
            }
        }
    }

    //========================
    // 家具配置判定
    //========================
    float x = floorPlan.x;
    float y = floorPlan.y;

    float width = floorPlan.width;
    float height = floorPlan.height;

    Rectangle roomArea = {300, 350, 600, 400};

    // L字用
    Rectangle roomAreaL1 = {0, 0, 0, 0};
    Rectangle roomAreaL2 = {0, 0, 0, 0};

    switch(room.roomType){

    case RoomType::Square:

        roomArea = {x, y, width, width};

        break;

    case RoomType::Vertical:
    case RoomType::Horizontal:

        roomArea = {x, y, width, height};

        break;

    case RoomType::LShape:

        // 上側の長方形
        roomAreaL1 = {x,y,width,height * 0.5f};

        // 左下側の長方形
        roomAreaL2 = {x,y + height * 0.5f,width * 0.6f,height * 0.5f};

        break;
    }

    //========================
    // 家具配置
    //========================
    if(!furnitureSettingVisible && !furnitureListVisible && selectedFurniture != FurnitureType::Count){

        Vector2 mousePos = GetMousePosition();

        bool canPlace = false;

        if(room.roomType == RoomType::LShape){
            // 上側 または 左下側なら配置可能
            canPlace = CheckCollisionPointRec(mousePos, roomAreaL1) || CheckCollisionPointRec(mousePos, roomAreaL2);

        }else{
            // 通常の部屋
            canPlace = CheckCollisionPointRec(mousePos, roomArea);
        }

        if(canPlace && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            FurnitureData &data = FurnitureList[(int)selectedFurniture];

            PlacedFurniture furniture;

            furniture.type = selectedFurniture;
            furniture.position = mousePos;

            // 現在設定している家具の色
            furniture.color = selectedColor;

            // 現在設定している家具の素材
            furniture.material = selectedMaterial;

            placedFurniture[questNumber - 1].push_back(furniture);

            // 配置後は選択解除
            selectedFurniture = FurnitureType::Count;
            selectedColor = Colors::Count;
            selectedMaterial = Materials::Count;
        }
    }

    //========================
    // 配置済み家具の移動
    //========================
    if(questNumber >= 1 && questNumber <= (int)placedFurniture.size()){
        auto &currentFurniture = placedFurniture[questNumber - 1];

        Vector2 mousePos = GetMousePosition();

        // ドラッグ開始
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && draggingFurnitureIndex == -1){
            // 後から描画された家具を優先
            for(int i = (int)currentFurniture.size() - 1; i >= 0; i--){

                PlacedFurniture &furniture = currentFurniture[i];
                FurnitureData &data = FurnitureList[(int)furniture.type];

                // 家具の判定範囲
                Rectangle furnitureRect = GetFurnitureRect(furniture, data);

                // 画像なし
                if(data.defaultTexture.id == 0){
                    furnitureRect = {furniture.position.x - data.size.x / 2.0f,furniture.position.y - data.size.y / 2.0f,data.size.x,data.size.y};
                }

                if(CheckCollisionPointRec(mousePos, furnitureRect)){
                    draggingFurnitureIndex = i;

                    // クリックした場所と家具中心のズレを保存
                    dragOffset = {mousePos.x - furniture.position.x,mousePos.y - furniture.position.y};

                    break;
                }
            }
        }

        // ドラッグ中
        if(draggingFurnitureIndex != -1 && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            PlacedFurniture &furniture = currentFurniture[draggingFurnitureIndex];

            furniture.position = {mousePos.x - dragOffset.x,mousePos.y - dragOffset.y};
        }

        // ドラッグ終了
        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
            draggingFurnitureIndex = -1;
        }
    }
}

void Room_layout::Draw(Font font){

    DrawTexturePro(titleBackground,{0,0,(float)titleBackground.width,(float)titleBackground.height},{0,0,1100,950},{0,0},0,WHITE);
    DrawRectangle(0,0,1100,950,Fade(BLACK,0.4f));

    DrawRectangleRec(questdetailBtn, WHITE);
    DrawTextEx(font, "依頼内容", {50, 30}, 25, 2, BLACK);

    DrawRectangleRec(furniturelist, BEIGE);
    DrawTextEx(font, "家具リスト", {30, 780}, 25, 2, BLACK);

    DrawTexturePro(all_list,{0, 0, (float)all_list.width, (float)all_list.height},{allfurnitureBtn.x, allfurnitureBtn.y, allfurnitureBtn.width, allfurnitureBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "全家具", {90, 855}, 25, 2, BLACK);

    DrawTexturePro(furniture_list,{0, 0, (float)furniture_list.width, (float)furniture_list.height},{furnitureBtn.x, furnitureBtn.y, furnitureBtn.width, furnitureBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "家具", {235, 855}, 25, 2, BLACK);

    DrawTexturePro(storage_list,{0, 0, (float)storage_list.width, (float)storage_list.height},{storageBtn.x, storageBtn.y, storageBtn.width, storageBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "収納", {370, 855}, 25, 2, BLACK);

    DrawTexturePro(electronics_list,{0, 0, (float)electronics_list.width, (float)electronics_list.height},{electronicsBtn.x, electronicsBtn.y, electronicsBtn.width, electronicsBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "家電", {505, 855}, 25, 2, BLACK);

    DrawTexturePro(hobby_list,{0, 0, (float)hobby_list.width, (float)hobby_list.height},{hobbyBtn.x, hobbyBtn.y, hobbyBtn.width, hobbyBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "趣味", {640, 855}, 25, 2, BLACK);

    DrawTexturePro(light_list,{0, 0, (float)light_list.width, (float)light_list.height},{lightBtn.x, lightBtn.y, lightBtn.width, lightBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "照明", {775, 855}, 25, 2, BLACK);

    DrawTexturePro(decoration_list,{0, 0, (float)decoration_list.width, (float)decoration_list.height},{decorationBtn.x, decorationBtn.y, decorationBtn.width, decorationBtn.height},{0, 0},0,WHITE);
    DrawTextEx(font, "装飾", {910, 855}, 25, 2, BLACK);

    DrawTextEx(font,TextFormat("部屋：%s", GetRoomTypeText(room.roomType)),{30, 100},35,2,BLACK);

    DrawTextEx(font,TextFormat("ドア：%s", GetDoorPositionText(room.door)),{30, 150},35,2,BLACK);

    DrawTextEx(font,TextFormat("窓①：%s", GetWindowPositionText(room.windows[0])),{30, 200},35,2,BLACK);

    if(room.windowCount == 2){
        DrawTextEx(font,TextFormat("窓②：%s", GetWindowPositionText(room.windows[1])),{30, 250},35,2,BLACK);
    }

    int gold = CalculateFurnitureCost();
    int maxGold = GetMaxGold();

    Color goldColor = ORANGE;
    if(gold > maxGold){
        goldColor = RED;
    }else{
        goldColor = ORANGE;
    }
    DrawTextEx(font,TextFormat("%dG/%dG", gold, maxGold),{30, 300},35,2,goldColor);

    DrawRectangleRec(setfurniture, BEIGE);
    DrawTextEx(font, "選択家具", {30, 350}, 35, 2, BLACK);

    DrawTextEx(font, "家具名：", {30, 400}, 35, 2, BLACK);

    // 家具名
    if(selectedFurniture != FurnitureType::Count){
        DrawTextEx(font,TextFormat("%s", FurnitureList[(int)selectedFurniture].name),{30, 450},23,2,BLACK);
    }else{
        DrawTextEx(font,"",{30, 450},23,2,BLACK);
    }

    // 色
    if(selectedColor != Colors::Count){
        DrawTextEx(font,TextFormat("色：%s", ColorList[(int)selectedColor].name),{30, 500},30,2,BLACK);
    }else{
        DrawTextEx(font,"色：",{30, 500},30,2,BLACK);
    }

    // 素材
    if(selectedMaterial != Materials::Count){
        DrawTextEx(font,TextFormat("素材：%s", MaterialList[(int)selectedMaterial].name),{30, 550},30,2,BLACK);
    }else{
        DrawTextEx(font,"素材：",{30, 550},30,2,BLACK);
    }

    DrawRoom();
    DrawDoor();
    DrawWindow();

    //========================
    // 配置済み家具描画
    //========================
    if(questNumber >= 1 && questNumber <= (int)placedFurniture.size()){
        for(const PlacedFurniture &furniture : placedFurniture[questNumber - 1]){
            FurnitureData &data = FurnitureList[(int)furniture.type];

            //==================================================
            // 家具画像がある場合
            //==================================================
            if(data.defaultTexture.id != 0){
                Rectangle dest = GetFurnitureRect(furniture, data);
                
                //==================================================
                // 使用する画像
                //==================================================
                Texture2D texture = data.defaultTexture;

                //==================================================
                // 素材が設定されている場合
                //==================================================
                if(furniture.material != Materials::Count){
                    int materialIndex = (int)furniture.material;

                    // 素材 + カラフル
                    if(furniture.color == Colors::Colorful){
                        if(data.materialcolorfulTexture[materialIndex].id != 0){
                            texture = data.materialcolorfulTexture[materialIndex];
                        }
                    }

                    // 素材 + 通常色
                    else{
                        if(data.materialTexture[materialIndex].id != 0){
                            texture = data.materialTexture[materialIndex];
                        }
                    }
                }
                //==================================================
                // 素材が設定されていない場合
                //==================================================
                else{
                    // カラフル
                    if(furniture.color == Colors::Colorful){
                        if(data.colorfulTexture.id != 0){
                            texture = data.colorfulTexture;
                        }
                    }

                    // 通常色
                    else{
                        texture = data.defaultTexture;
                    }
                }

                //==================================================
                // 使用する色
                //==================================================
                Color furnitureColor = WHITE;

                if(furniture.color != Colors::Count && furniture.color != Colors::Colorful){
                    furnitureColor = GetRaylibColor(furniture.color);
                }

                //==================================================
                // 描画
                //==================================================
                DrawTexturePro(texture,{0,0,(float)texture.width,(float)texture.height},dest,{0, 0},0,furnitureColor);
            }
            //==================================================
            // 家具画像がない場合 → 四角
            //==================================================
            else{
                Rectangle furnitureRect = {furniture.position.x - data.size.x / 2.0f,furniture.position.y - data.size.y / 2.0f,data.size.x,data.size.y};

                // レインボー
                if(furniture.color == Colors::Colorful){
                    float width = furnitureRect.width / 6.0f;

                    Color rainbow[] =
                    {
                        RED,
                        ORANGE,
                        YELLOW,
                        GREEN,
                        BLUE,
                        PURPLE
                    };

                    for(int i = 0; i < 6; i++){
                        DrawRectangle(furnitureRect.x + width * i,furnitureRect.y,width,furnitureRect.height,rainbow[i]);
                    }
                }else{ // 通常色
                    Color furnitureColor = GetRaylibColor(furniture.color);

                    DrawRectangleRec(furnitureRect,furnitureColor);

                    // 白なら黒枠
                    if(furniture.color == Colors::White){
                        DrawRectangleLinesEx(furnitureRect,2.0f,BLACK);
                    }
                }
            }
        }
    }

    //========================
    // 配置済み家具の削除
    // Dキー
    //========================
    if(questNumber >= 1 && questNumber <= (int)placedFurniture.size()){
        auto &currentFurniture = placedFurniture[questNumber - 1];

        for(int i = (int)currentFurniture.size() - 1; i >= 0; i--){
            PlacedFurniture &furniture = currentFurniture[i];

            FurnitureData &data = FurnitureList[(int)furniture.type];

            Rectangle furnitureRect;

            //==================================================
            // 家具画像がある場合
            //==================================================
            if(data.defaultTexture.id != 0){
                furnitureRect = GetFurnitureRect(furniture, data);
            }
            //==================================================
            // 家具画像がない場合
            //==================================================
            else{
                furnitureRect = {furniture.position.x - data.size.x / 2.0f,furniture.position.y - data.size.y / 2.0f,data.size.x,data.size.y};
            }

            //==================================================
            // マウスが家具の上にあり、Dキーが押された
            //==================================================
            if(CheckCollisionPointRec(GetMousePosition(), furnitureRect) && IsKeyPressed(KEY_D)){
                currentFurniture.erase(currentFurniture.begin() + i);

                break;
            }
        }
    }

    //========================
    // 家具リスト描画
    //========================
    if(furnitureListVisible && !furnitureSettingVisible){
        DrawRectangle(200,100,840,650,BEIGE);
        int index = 0;

        //並び替え
        std::vector<int> drawList;

        for(int i = 0; i < (int)FurnitureType::Count; i++){
            FurnitureData &data = FurnitureList[i];

            // 解放条件
            if((int)data.unlock > questNumber){
                continue;
            }

            // カテゴリー
            if(currentCategory != FurnitureCategory::All && data.category != currentCategory){
                continue;
            }

            drawList.push_back(i);
        }

        //defaultOrderでソート
        std::sort(drawList.begin(), drawList.end(),[](int a, int b){return FurnitureList[a].defaultOrder <FurnitureList[b].defaultOrder;});

        //描画
        for(int index = 0; index < (int)drawList.size(); index++){
            FurnitureData &data = FurnitureList[drawList[index]];

            int col = index % columns;
            int row = index / columns;

            Vector2 pos ={startX + col * colWidth,startY + row * rowHeight};

            DrawTextEx(font, data.name, pos, 25, 2, BLACK);
        }
    }else if(furnitureSettingVisible){ //詳細設定画面
        FurnitureData &data = FurnitureList[(int)selectedFurniture];

        DrawRectangleRec(furnitureSetting, (Color){255, 225, 186, 255});

        // 文字サイズを取得
        Vector2 textSize = MeasureTextEx(font, data.name, 50, 2);

        // 中央揃え(Xのみ)
        float textX = furnitureSetting.x + (furnitureSetting.width - textSize.x) / 2.0f;

        DrawTextEx(font,data.name,{textX,100},50,2,BLACK);

        DrawRectangleRec(settingCancelBtn, RED);
        DrawTextEx(font, "やめる", {200, 100}, 25, 2, BLACK);

        DrawRectangleRec(settingDecisionBtn, BLUE);
        DrawTextEx(font, "決定", {770, 100}, 25, 2, BLACK);

        DrawRectangleRec(settingColorBtn, (Color){187, 255, 233, 255});
        DrawTextEx(font, "色選択", {200, 530}, 25, 2, BLACK);

        DrawRectangleRec(settingMaterialBtn, (Color){187, 255, 233, 255});
        DrawTextEx(font, "素材選択", {200, 600}, 25, 2, BLACK);

        //========================
        // 家具画像
        //========================
        Texture2D texture = data.defaultTexture;

        //==================================================
        // 素材が選択されている場合
        //==================================================
        if(selectedMaterial != Materials::Count){
            int materialIndex = (int)selectedMaterial;

            //==================================================
            // 素材 + カラフル
            //==================================================
            if(selectedColor == Colors::Colorful){
                if(data.materialcolorfulTexture[materialIndex].id != 0){
                    texture = data.materialcolorfulTexture[materialIndex];
                }
            }
            //==================================================
            // 素材 + 通常色
            //==================================================
            else{
                if(data.materialTexture[materialIndex].id != 0){
                    texture = data.materialTexture[materialIndex];
                }
            }
        }
        //==================================================
        // 素材が選択されていない場合
        //==================================================
        else{
            //==================================================
            // カラフル
            //==================================================
            if(selectedColor == Colors::Colorful){
                if(data.colorfulTexture.id != 0){
                    texture = data.colorfulTexture;
                }
            }
            //==================================================
            // 色なし
            //==================================================
            else{
                texture = data.defaultTexture;
            }
        }

        //==================================================
        // 画像サイズ
        //==================================================
        float maxWidth = 500.0f;
        float maxHeight = 300.0f;

        // 元画像のサイズ
        float imageWidth = (float)texture.width;
        float imageHeight = (float)texture.height;

        // 縦横比を維持
        float scaleX = maxWidth / imageWidth;
        float scaleY = maxHeight / imageHeight;

        float scale = std::min(scaleX, scaleY);

        // 実際に表示するサイズ
        float drawWidth = imageWidth * scale;
        float drawHeight = imageHeight * scale;

        // 枠の中央に配置
        float drawX = furnitureSetting.x + (furnitureSetting.width - drawWidth) / 2.0f;
        float drawY = 150.0f;

        //==================================================
        // 色
        //==================================================
        Color furnitureColor = WHITE;

        // 通常色の場合だけ色を適用
        if(selectedColor != Colors::Count && selectedColor != Colors::Colorful){
            furnitureColor = GetRaylibColor(selectedColor);
        }

        //==================================================
        // 描画
        //==================================================
        DrawTexturePro(
            texture,

            // 元画像全体
            {
                0,
                0,
                imageWidth,
                imageHeight
            },

            // 表示先
            {
                drawX,
                drawY,
                drawWidth,
                drawHeight
            },

            {0, 0},
            0,
            furnitureColor
        );

        // 色選択画面
        if(colorSelectVisible){
            DrawColorSelect(font);
        }

        // 素材選択画面
        if(materialSelectVisible){
            DrawMaterialSelect(font);
        }
    }
}

int Room_layout::GetFurnitureCost(const PlacedFurniture &furniture){
    // 家具の基本価格
    int cost = FurnitureList[(int)furniture.type].baseCost;

    // 素材価格を追加
    if(furniture.material != Materials::Count){
        cost += MaterialCost[(int)furniture.material];
    }

    return cost;
}

int Room_layout::CalculateFurnitureCost(){
    int totalCost = 0;

    if(questNumber >= 1 && questNumber <= (int)placedFurniture.size()){
        for(const PlacedFurniture &furniture : placedFurniture[questNumber - 1]){
            totalCost += GetFurnitureCost(furniture);
        }
    }

    return totalCost;
}

int Room_layout::GetMaxGold(){
    // 高級感を最優先
    if(style == Style::Luxury || priority == Priority::Luxury){
        return 15000;
    }

    // コスト重視
    if(priority == Priority::Cost){
        return 9000;
    }

    return 12000;
}

void Room_layout::SetUnlockLevel(UnlockLevel level){

    currentLevel = level;
}

void Room_layout::SetQuest(RoomData data,int number,Priority priorityData,Style styleData){
    room = data;
    questNumber = number;

    priority = priorityData;
    style = styleData;

    CreateFloorPlan();
}

int Room_layout::Getbottan_number() const{

    return bottan_number;
}

void Room_layout::ResetBottanNumber(){
    bottan_number = 0;
}

void Room_layout::ResetSetting(){

    // 詳細設定画面を閉じる
    furnitureSettingVisible = false;

    // 色選択画面を閉じる
    colorSelectVisible = false;

    // 素材選択画面を閉じる
    materialSelectVisible = false;

    // 選択中家具を解除
    selectedFurniture = FurnitureType::Count;

    // 選択色を初期化
    selectedColor = Colors::Count;

    // 選択素材を初期化
    selectedMaterial = Materials::Count;
}

void Room_layout::SetRequestData(Priority priority, Style style)
{
    currentPriority = priority;
    currentStyle = style;
}

// 配置済み家具の判定範囲
Rectangle Room_layout::GetFurnitureRect(const PlacedFurniture &furniture, const FurnitureData &data){
    float imageScaleX = 2.0f;
    float imageScaleY = 1.2f;

    float drawWidth = data.size.x * imageScaleX;
    float drawHeight = data.size.y * imageScaleY;

    return {
        furniture.position.x - drawWidth / 2.0f,
        furniture.position.y - drawHeight / 2.0f,
        drawWidth,
        drawHeight
    };
}

//==================================================
// 画像の透明部分を除いた範囲を取得
//==================================================
Rectangle Room_layout::GetImageAlphaBounds(Image image){
    Color *pixels = LoadImageColors(image);

    int minX = image.width;
    int minY = image.height;
    int maxX = -1;
    int maxY = -1;

    // 画像を1ピクセルずつ確認
    for(int y = 0; y < image.height; y++){
        for(int x = 0; x < image.width; x++){
            Color pixel = pixels[y * image.width + x];

            // 完全透明ではない
            if(pixel.a > 0){
                if(x < minX){
                    minX = x;
                }
                if(y < minY){
                    minY = y;
                }
                if(x > maxX){
                    maxX = x;
                }
                if(y > maxY){
                    maxY = y;
                }
            }
        }
    }

    UnloadImageColors(pixels);

    // 全て透明だった場合
    if(maxX == -1){
        return {0, 0, 0, 0};
    }

    return {
        (float)minX,
        (float)minY,
        (float)(maxX - minX + 1),
        (float)(maxY - minY + 1)
    };
}