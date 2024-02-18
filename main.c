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

    Texture2D globalTextureList[10] = {meteor, meteor20, meteor30, meteor60};

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    
    // Loading entities into one array and saving their ID - array position index
    playerId = SyLoadEntities(player, playerAmount , globalEntityList, 300, &entitiesNumber);
    redMeteorsId = SyLoadEntities(redMeteors, redMeteorsAmount , globalEntityList, 300, &entitiesNumber);
    greenMeteorsId = SyLoadEntities(greenMeteors, greenMeteorsAmount , globalEntityList, 300, &entitiesNumber);

    // Assigning default components to all entities
    SyInitializeEntity(globalEntityList,entitiesNumber, screenWidth, screenHeight);
    
    // Characterising entities with Player's ID as 0
    SyInitializeSpecialEntity(globalEntityList, playerId, playerAmount, 0, 0);    
    SyInitializeSpecialEntity(globalEntityList, redMeteorsId, redMeteorsAmount, 1, 0);
    SyInitializeSpecialEntity(globalEntityList, greenMeteorsId, greenMeteorsAmount, 2, 200);

    // Setting up the player model
    SyPositionSingleEntity(globalEntityList,0,0,0);
    SyColorSingleEntity(globalEntityList, 0, RAYWHITE);
    
    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose())
    {
        if (!gameLost) {
            SyMoveSingleEntity(globalEntityList,0,1010);
            SyGravity(globalEntityList,entitiesNumber, gravityAcceleration);
            SyDetectPlayerCollision(globalEntityList,globalEntityList,entitiesNumber,100);
            SyDetectCircleCollision(globalEntityList, entitiesNumber,200, &gravityAcceleration);
            
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTexture(background,0,0,WHITE);
            DrawText(TextFormat("gravityAcceleration: %d", gravityAcceleration), 0, 0, 20, RED);

            SyRenderEntity(globalEntityList, playerId, playerAmount, 0, globalTextureList,0);
            SyRenderEntity(globalEntityList, redMeteorsId, redMeteorsAmount, 1, globalTextureList,1);
            SyRenderEntity(globalEntityList, greenMeteorsId, greenMeteorsAmount, 2, globalTextureList,2);

            EndDrawing();

            SyResetPosition(globalEntityList,entitiesNumber, screenWidth, screenHeight);
        } else 
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("GAME OVER", 0, 0, 20, RED);

        }
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

 