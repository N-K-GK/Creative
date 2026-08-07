#include "raylib.h"
#include "Game.h"
#include "Room.h"
#include <random>
#include <ctime>

int main(){
    srand(time(NULL));

    SetRandomSeed(time(nullptr));
    
    InitWindow(1100, 950, "Creative Director");

    SetTargetFPS(60);

    Game game;

    while(!WindowShouldClose()){

        game.Update();

        BeginDrawing();

        ClearBackground(SKYBLUE);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}