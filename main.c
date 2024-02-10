#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


int main (void)
{

    // Initialization

    // Declarations
    const int screenWidth = 1280;
    const int screenHeight = 960;
    const int entitiesNumber = 100;

    EnEntity globalEntityList[entitiesNumber];
    
    SyInitializeEntity(globalEntityList,entitiesNumber);
    SyPositionSingleEntity(globalEntityList,0,0,0);
    SyColorSingleEntity(globalEntityList, 0, RAYWHITE);
    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "matrixGame");
    while (!WindowShouldClose())
    {
        SyMoveSingleEntity(globalEntityList,0);
        SyDetectCollision(globalEntityList,globalEntityList,entitiesNumber,10);
        BeginDrawing();

        ClearBackground(BLACK);

        SyRenderEntity(globalEntityList,entitiesNumber);
        SyGravity(globalEntityList,entitiesNumber);
        SyResetPosition(globalEntityList,entitiesNumber,screenHeight);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

 