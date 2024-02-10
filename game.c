#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// Functions initialization

void SyInitializeEntity(EnEntity * globalEntityList, int entityCounter)
{
    srand(time(NULL));
    int x,y,xmin,xmax,ymin,ymax;
    xmin = 10;
    ymin = 10;
    xmax = 1270;
    ymax = 950;

    for (int i = 0; i < entityCounter; i++)
    {
        x = xmin + rand() % (xmax - xmin + 1);
        y = ymin + rand() % (ymax - ymin + 1);

        globalEntityList[i].id = i;
        globalEntityList[i].color = GREEN;
        globalEntityList[i].CoPosition.status = 1;
        globalEntityList[i].CoPosition.x = x;
        globalEntityList[i].CoPosition.y = y;
    }

}

void SyColorSingleEntity(EnEntity *globalEntityList, int entityId,Color ChoosenColor)
{
    globalEntityList[entityId].color = ChoosenColor;

}

void SyPositionSingleEntity(EnEntity *globalEntityList, int entityId, int x, int y)
{
    globalEntityList[entityId].CoPosition.status = 1;
    globalEntityList[entityId].CoPosition.x = x;
    globalEntityList[entityId].CoPosition.y = y;

}

void SyMoveSingleEntity(EnEntity *globalEntityList, int entityId) 
{

    if (IsKeyDown(KEY_RIGHT))
    {
        globalEntityList[entityId].CoPosition.x += GetFrameTime()*1000;
    } 

    if (IsKeyDown(KEY_LEFT))
    {
        globalEntityList[entityId].CoPosition.x -=  GetFrameTime()*1000;
    }


    if (IsKeyDown(KEY_UP))
    {
        globalEntityList[entityId].CoPosition.y -= GetFrameTime()*1000;
    } 

    if (IsKeyDown(KEY_DOWN))
    {
        globalEntityList[entityId].CoPosition.y +=  GetFrameTime()*1000;
    }
   
}
void SyGravity(EnEntity *globalEntityList, int entityCounter)
{

    for (int i = 1; i <= entityCounter;i++)
    {
        globalEntityList[i].CoPosition.y += 1;
    }

}

void SyResetPosition(EnEntity *globalEntityList, int entityCounter, int screenHeight)
{
    for (int i = 1; i <= entityCounter; i++)
    {
        if (globalEntityList[i].CoPosition.y >= screenHeight)
        {
            globalEntityList[i].CoPosition.y = 0;
        }
    }
}

void SyRenderEntity(EnEntity *globalEntityList, int entityCounter)
{
    for (int i = 0; i < entityCounter; i++)
    {
        if (globalEntityList[i].CoPosition.status != 0) 
        {
            DrawRectangle(globalEntityList[i].CoPosition.x, globalEntityList[i].CoPosition.y, 10, 10, globalEntityList[i].color);
        }
    }
}

void SyDetectCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius)
{

    // Collecting player position

    int playerX = globalEntityList[0].CoPosition.x;
    int playerY = globalEntityList[0].CoPosition.y;

    for (int i = 1; i <= entityCounter; i++)
    {

        if ((abs(playerX - globalEntityList[i].CoPosition.x) < radius) && (abs(playerY - globalEntityList[i].CoPosition.y) < radius))
        {
            globalEntityList[i].color = RED;
        }
    }
}

// void SyRenderCollisionCircle