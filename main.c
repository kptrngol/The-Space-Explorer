#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


int main (void)
{

    // Initialization

    // Texture

    Texture2D background;

    // Declarations
    const int screenWidth = 1280;
    const int screenHeight = 960;
    const int redObstacleCount = 15;
    const int greenObstacleCount = 100;
    const int entitiesNumber = 1 + greenObstacleCount + redObstacleCount;
    // entities {1x player, 100x green obstacles, 15x red obstacles}
    const int specialEntityFirstId = entitiesNumber - redObstacleCount;

    EnEntity globalEntityList[entitiesNumber];
    
    SyInitializeEntity(globalEntityList,entitiesNumber);
    SyInitializeSpecialEntity (globalEntityList, entitiesNumber, specialEntityFirstId, entitiesNumber, 1, 70);
    SyPositionSingleEntity(globalEntityList,0,0,0);
    SyColorSingleEntity(globalEntityList, 0, RAYWHITE);
    SetTargetFPS(60);

    InitWindow(screenWidth, screenHeight, "matrixGame");

    
    // Load textures
    background = LoadTexture("./assets/background.png");



    while (!WindowShouldClose())
    {

        SyMoveSingleEntity(globalEntityList,0);
        
        SyDetectPlayerCollision(globalEntityList,globalEntityList,entitiesNumber,10);
        BeginDrawing();

        ClearBackground(BLACK);
        DrawTexture(background,0,0,WHITE);

        SyRenderEntity(globalEntityList,entitiesNumber);
        SyGravity(globalEntityList,entitiesNumber);
        SyResetPosition(globalEntityList,entitiesNumber,screenHeight);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

 