#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include "game.h"


int main (void)
{
    // Declaring and loading textures after window initialisation
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

    Texture2D globalTextureList[10] = {meteor};


    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    
    // Loading entities into one array and saving their ID - array position index
    redMeteorsId = SyLoadEntities(redMeteors, redMeteorsAmount , globalEntityList, 300, &entitiesNumber);
    greenMeteorsId = SyLoadEntities(greenMeteors, greenMeteorsAmount , globalEntityList, 300, &entitiesNumber);

    // Assigning default components to all entities
    SyInitializeEntity(globalEntityList,entitiesNumber, screenWidth, screenHeight);
    
    // Characterising entities
    SyInitializeSpecialEntity(globalEntityList, redMeteorsId, redMeteorsAmount, entitiesNumber, 1, 70);
    SyInitializeSpecialEntity(globalEntityList, greenMeteorsId, greenMeteorsAmount, entitiesNumber, 2, 70);

    // Setting up the player model
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

    // Unload textures

    UnloadTexture(background);
    UnloadTexture(meteor);
    UnloadTexture(meteor20);
    UnloadTexture(meteor30);
    UnloadTexture(meteor60);


    CloseWindow();
    return 0;
}

 