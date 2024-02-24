#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "game.h"


int main (void)
{
    // Declaring and loading textures after window initialisation
    Music musicTheme;
    
    Texture2D background;
    Texture2D starship;
    Texture2D meteor20;
    Texture2D meteor30;
    Texture2D meteor60;

    InitWindow(0, 0, "matrixGame");
    InitAudioDevice();

    musicTheme = LoadMusicStream("./assets/ostheme.mp3");
    background = LoadTexture("./assets/background.png");
    starship = LoadTexture("./assets/starship.png");
    meteor20 = LoadTexture("./assets/meteor.png");
    meteor30 = LoadTexture("./assets/meteor.png");
    meteor60 = LoadTexture("./assets/meteor.png");

    Texture2D globalTextureList[10] = {starship, meteor20, meteor30, meteor60};

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
    SyPositionSingleEntity(globalEntityList,0,1,screenHeight/2);
    SyColorSingleEntity(globalEntityList, 0, RAYWHITE);
    
    PlayMusicStream(musicTheme);
    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose())
    {
        if (!gameLost) {
            UpdateMusicStream(musicTheme);
            scrollingBack -= 20.5f;
            if (abs(scrollingBack) >= background.width*6) { scrollingBack = 0.0f;}
            SyMoveSingleEntity(globalEntityList,0,&speedX, screenWidth, screenHeight);
            SyGravity(globalEntityList,entitiesNumber, gravityAcceleration);
            SyDetectPlayerCollision(globalEntityList,globalEntityList,entitiesNumber,100);
            SyDetectCircleCollision(globalEntityList, entitiesNumber,200, &gravityAcceleration);
            
            BeginDrawing();

                ClearBackground(BLACK);
                DrawTextureEx(background,(Vector2){scrollingBack,0}, 0.0f, 6.0f,WHITE);
                DrawTextureEx(background,(Vector2){scrollingBack + background.width*6,0}, 0.0f, 6.0f,WHITE);
                DrawText(TextFormat("scroll: %f", scrollingBack), 0, 20, 20, RED);
                DrawText(TextFormat("gravityAcceleration: %f", gravityAcceleration), 0, 40, 20, RED);
                DrawText(TextFormat("speed: %f", speedX), 0, 60, 20, RED);

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
    UnloadMusicStream(musicTheme);
    UnloadTexture(background);
    UnloadTexture(starship);
    UnloadTexture(meteor20);
    UnloadTexture(meteor30);
    UnloadTexture(meteor60);


    CloseAudioDevice();
    CloseWindow();
    return 0;
}

 