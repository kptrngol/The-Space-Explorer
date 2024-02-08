#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


int main (void)
{

    // Initialization

    const int screenWidth = 1280;
    const int screenHeight = 960;

    EnEntity globalEntityList[500];
    SyInitializeEntity(globalEntityList,500);
    SyPositionSingleEntity(globalEntityList,0,0,0);
    SyColorSingleEntity(globalEntityList, 0, RAYWHITE);
    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "platformer Demo");
    while (!WindowShouldClose())
    {
        SyMoveSingleEntity(globalEntityList,0);

        BeginDrawing();

        ClearBackground(BLACK);

        SyRenderEntity(globalEntityList,500);
        SyGravity(globalEntityList,500);
        SyResetPosition(globalEntityList,500,screenHeight);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

 