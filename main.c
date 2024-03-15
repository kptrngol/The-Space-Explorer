#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "story.h"
#include "game.h"


int main (void)
{


    // Declaring and loading textures after window initialisation
    Music musicTheme;
    
    Texture2D background;
    Texture2D second_background;

    Texture2D starship;
    Texture2D meteor20;
    Texture2D meteor30;
    Texture2D meteor60;

    InitWindow(0, 0, "the lone space");
    InitAudioDevice();

    const int screenWidth = GetMonitorWidth(0);
    const int screenHeight = GetMonitorHeight(0);
    musicTheme = LoadMusicStream("./assets/dust.mp3");
    background = LoadTexture("./assets/background.png");
    second_background = LoadTexture("./assets/second_background.png");
    starship = LoadTexture("./assets/starship.png");
    meteor20 = LoadTexture("./assets/asteroid.png");
    meteor30 = LoadTexture("./assets/asteroid.png");
    meteor60 = LoadTexture("./assets/asteroid.png");

    Texture2D globalTextureList[10] = {starship, meteor20, meteor30, meteor60};
    
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
        while (!exitGame)
        {
            switch (gameState)
            {
                case MENU:
                    if (!(IsKeyPressed(KEY_ESCAPE)))
                    {
                        UpdateMusicStream(musicTheme);

                        if (IsKeyPressed(KEY_ENTER))
                        {
                            gameState = GAME;
                        }

                        BeginDrawing();
                            ClearBackground(BLACK);
                            DrawText("the lone space", screenWidth/2-(MeasureText("the lone space",32)/2), screenHeight/2, 32, DARKGRAY);
                            // DrawRectangle(int posX, int posY, int width, int height, Color color);                            
                            DrawText("enter* the shuttle", screenWidth/2-(MeasureText("enter the shuttle",16)/2), screenHeight/2 + 32, 16, WHITE);
                            DrawText("escape* the shuttle", screenWidth/2-(MeasureText("escape the shuttle",16)/2), screenHeight/2 + 48, 16, GRAY);
                        EndDrawing();
                    } else {
                        exitGame = 1;
                        // CloseWindow();
                    }
                    break;
                
                case GAMEOVER:
                    if ((!(IsKeyPressed(KEY_ESCAPE))))
                    {
                    
                        UpdateMusicStream(musicTheme);

                        BeginDrawing();
                            ClearBackground(BLACK);

                            if (IsKeyPressed(KEY_ENTER))
                            {
                                gameState = GAME;
                                gameLost = 0;
                                // Initialize game settings
                                SyInitializeEntity(globalEntityList,entitiesNumber, screenWidth, screenHeight);
                                SyPositionSingleEntity(globalEntityList,0,1,screenHeight/2);
                                int gameLost = 0;
                                int spacePoitns = 0;
                                float gravityAcceleration = 2.0f;
                                int collisionCooldownStatus = 0;
                                float collisionCooldownTimer = 0.0f;
                                int boostCooldownStatus = 0;
                                float boostCooldownTimer = 0.0f;
                                int boostStatus = 0;
                                float boostTimer = 0.0f;

                            }
                            DrawText("signal lost", screenWidth/2-(MeasureText("signal lost",32)/2), screenHeight/2, 32, RED);                            
                            DrawText(TextFormat("distance: %d", spacePoitns), screenWidth/2-(MeasureText(TextFormat("distance: %d", spacePoitns),16)/2), screenHeight/2 + 32, 16, WHITE);
                            DrawText("enter* the repair mode", screenWidth/2-(MeasureText("enter* the repair mode",16)/2), screenHeight/2 + 48, 16, WHITE);

                            // DrawText("game: konrad petrenko-goljanek", screenWidth/2-(MeasureText("game: konrad petrenko-goljanek",16)/2), screenHeight/2 + 150, 16, PURPLE);
                            // DrawText("music: mateusz kurek", screenWidth/2-(MeasureText("music: mateusz kurek",16)/2), screenHeight/2 + 200, 16, PURPLE);
                        
                        EndDrawing();
                    } else {
                        exitGame = 1;
                        // CloseWindow();
                    }
                    break;

                case GAME:
                    if ((!(gameLost>=3))) 
                    {

                        if (IsKeyPressed(KEY_ESCAPE))
                        {
                            gameState = MENU;
                        }

                        UpdateMusicStream(musicTheme);
                        spacePoitns++;
                        scrollingBack -= 10.5f;

                        if (abs(scrollingBack) >= background.width*6) { scrollingBack = 0.0f;}

                        // Update objects position
                        SyMoveSingleEntity(globalEntityList,0,&speedX, screenWidth, screenHeight);
                        SyGravity(globalEntityList,entitiesNumber, gravityAcceleration);
                        SyUpdateTextureCenter(globalEntityList,entitiesNumber);

                        // Detect Collision 
                        SyDetectPlayerCollision(globalEntityList,globalEntityList,entitiesNumber,(113), &gameLost, 65, 65);
                        SyDetectCircleCollision(globalEntityList, entitiesNumber,200, &gravityAcceleration);
                        SyCooldownUpdate(&collisionCooldownTimer, &collisionCooldownStatus, COOLDOWNTIME);
                        if(boostStatus == 1)
                        {
                            SyTimerDependantActionUpdate(&boostTimer, &boostStatus, BOOSTTIME, &boostCooldownStatus, &boostCooldownTimer);
                        }
                        SyCooldownUpdate(&boostCooldownTimer, &boostCooldownStatus, BOOSTCOOLDOWNTIME);
                        
                        BeginDrawing();

                            ClearBackground(BLACK);

                            // Draw background
                            DrawTextureEx(background,(Vector2){scrollingBack,0}, 0.0f, 6.0f,WHITE);
                            DrawTextureEx(background,(Vector2){scrollingBack + background.width*6,0}, 0.0f, 6.0f,WHITE);

                            DrawTextureEx(second_background,(Vector2){scrollingBack,0}, 0.0f, 6.0f,WHITE);
                            DrawTextureEx(second_background,(Vector2){scrollingBack + second_background.width*6,0}, 0.0f, 6.0f,WHITE);

                            // Progress info
                            DrawText(TextFormat("distance: %d", spacePoitns), 10, 20, 16, WHITE);
                            DrawText(TextFormat("acceleration: %f", gravityAcceleration), 10, 40, 16, WHITE);
                            DrawText(TextFormat("shuttle damage: %d/3", gameLost), 10, 60, 16, RED);

                            // Debug info
                            DrawText(TextFormat("fps: %d", GetFPS()), screenWidth-(MeasureText("fps",16))-100, 20, 16, GRAY);
                            DrawText(TextFormat("cooldown: %f", collisionCooldownTimer), screenWidth-(MeasureText("cooldown",16))-100, 40, 16, GRAY);
                            DrawText(TextFormat("cooldown st.: %d", collisionCooldownStatus), screenWidth-(MeasureText("cooldown st.",16))-100, 60, 16, GRAY);
                            DrawText(TextFormat("speed: %f", speedX), screenWidth-(MeasureText("speed",16))-100, 80, 16, GRAY);
                            DrawText(TextFormat("boostcooldown: %f", boostCooldownTimer), screenWidth-(MeasureText("boostcooldown",16))-100, 100, 16, GRAY);
                            DrawText(TextFormat("boostcooldown st.: %d", boostCooldownStatus), screenWidth-(MeasureText("boostcooldown st.",16))-100, 120, 16, GRAY);
                            DrawText(TextFormat("boost: %f", boostTimer), screenWidth-(MeasureText("boostcooldown",16))-100, 140, 16, GRAY);
                            DrawText(TextFormat("boost st.: %d", boostStatus), screenWidth-(MeasureText("boostcooldown st.",16))-100, 160, 16, GRAY);
                            
                            // Game dialog box

                            // Render

                            SyRenderEntity(globalEntityList, playerId, playerAmount, 0, globalTextureList,0);
                            DrawCircleLines(globalEntityList[0].position.x+(65/2), globalEntityList[0].position.y+(65/2),30, YELLOW);
                            SyRenderEntity(globalEntityList, redMeteorsId, redMeteorsAmount, 1, globalTextureList,1);
                            SyRenderEntity(globalEntityList, greenMeteorsId, greenMeteorsAmount, 2, globalTextureList,2);

                        EndDrawing();

                        SyResetPosition(globalEntityList,entitiesNumber, screenWidth, screenHeight);
                    } else 
                    {
                        gameState = GAMEOVER;
                    }
                    break;
            }
        } 
    }

    // Unload textures
    UnloadMusicStream(musicTheme);
    UnloadTexture(background);
    UnloadTexture(second_background);
    UnloadTexture(starship);
    UnloadTexture(meteor20);
    UnloadTexture(meteor30);
    UnloadTexture(meteor60);


    CloseAudioDevice();
    CloseWindow();
    return 0;
}

 