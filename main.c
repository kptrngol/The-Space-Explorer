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
    
    // PlayMusicStream(musicTheme);
    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose())
    {
        if ((!gameLost)) {
            // UpdateMusicStream(musicTheme);
            spacePoitns++;
            scrollingBack -= 20.5f;

            if (abs(scrollingBack) >= background.width*6) { scrollingBack = 0.0f;}

            // Update objects position
            SyMoveSingleEntity(globalEntityList,0,&speedX, screenWidth, screenHeight);
            SyGravity(globalEntityList,entitiesNumber, gravityAcceleration);
            SyUpdateTextureCenter(globalEntityList,entitiesNumber);

            // Detect Collision 
            SyDetectPlayerCollision(globalEntityList,globalEntityList,entitiesNumber,(113/2), &gameLost, 65, 65);
            SyDetectCircleCollision(globalEntityList, entitiesNumber,200, &gravityAcceleration);
            
            BeginDrawing();

                ClearBackground(BLACK);

                // Draw background
                DrawTextureEx(background,(Vector2){scrollingBack,0}, 0.0f, 6.0f,WHITE);
                DrawTextureEx(background,(Vector2){scrollingBack + background.width*6,0}, 0.0f, 6.0f,WHITE);
                DrawText(TextFormat("SPACE POINTS: %d", spacePoitns), 0, 20, 20, WHITE);
                DrawText(TextFormat("ACCELERATION: %f", gravityAcceleration), 0, 40, 20, WHITE);
                
                // Render

                SyRenderEntity(globalEntityList, playerId, playerAmount, 0, globalTextureList,0);
                DrawCircleLines(globalEntityList[0].position.x+(65/2), globalEntityList[0].position.y+(65/2),30, YELLOW);
                SyRenderEntity(globalEntityList, redMeteorsId, redMeteorsAmount, 1, globalTextureList,1);
                SyRenderEntity(globalEntityList, greenMeteorsId, greenMeteorsAmount, 2, globalTextureList,2);

            EndDrawing();

            SyResetPosition(globalEntityList,entitiesNumber, screenWidth, screenHeight);
        } else 
        {
            BeginDrawing();
                ClearBackground(BLACK);
                DrawText("GAME OVER", screenWidth/2-(MeasureText("GAME OVER",100)/2), screenHeight/2-50, 100, RED);
                DrawText(TextFormat("SCORE: %d", spacePoitns), screenWidth/2-(MeasureText(TextFormat("SCORE: %d", spacePoitns),32)/2), screenHeight/2 + 50, 32, WHITE);

            EndDrawing();
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

 