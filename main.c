#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


int main (void)
{

    Texture2D background;
    Texture2D meteor;
    Texture2D meteor20;
    Texture2D meteor30;
    Texture2D meteor60;

    InitWindow(0, 0, "matrixGame");

    background = LoadTexture("./assets/background.png");
    meteor = LoadTexture("./assets/meteor.png");
    meteor20 = LoadTexture("./assets/meteor.png");
    meteor30 = LoadTexture("./assets/meteor.png");
    meteor60 = LoadTexture("./assets/meteor.png");

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    
    SyLoadEntities(redMeteors, 10, globalEntityList, 300, &SyLoadEntitiesCounter);
    SyLoadEntities(greenMeteors, 10, globalEntityList, 300, &SyLoadEntitiesCounter);

    SyInitializeEntity(globalEntityList,entitiesNumber, screenWidth, screenHeight);
    
    SyInitializeSpecialEntity (globalEntityList, entitiesNumber, specialEntityFirstId, entitiesNumber, 1, 70);

    // SyAssignTextures(globalEntityList, entitiesNumber);
    SyPositionSingleEntity(globalEntityList,0,0,0);
    
    SyColorSingleEntity(globalEntityList, 0, RAYWHITE);
    
    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose())
    {

        SyMoveSingleEntity(globalEntityList,0,1010);
        SyGravity(globalEntityList,entitiesNumber, 1);
        SyDetectPlayerCollision(globalEntityList,globalEntityList,entitiesNumber,10);
        
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(background,0,0,WHITE);
        SyRenderEntity(globalEntityList,entitiesNumber, meteor);
        EndDrawing();

        SyResetPosition(globalEntityList,entitiesNumber,screenHeight);

        // SyResetCollisionStatus(globalEntityList, entitiesNumber);
    }

    // freeAssets();

    CloseWindow();
    return 0;
}

 