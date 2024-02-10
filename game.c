#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// Functions initialization

void SyInitializeEntity(EnEntity *globalEntityList, int entityCounter)
{
    srand(time(NULL));
    int x,y,xmin,xmax,ymin,ymax;
    xmin = 60;
    ymin = 0;
    xmax = 1260;
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

void SyInitializeSpecialEntity (EnEntity *globalEntityList, int entityCounter, int specialEntityFirstId, int specialEntityCounter, int type, int radius)
{
    for (int i = specialEntityFirstId; i < specialEntityCounter; i++)
    {
        if (type == 1)
        {
            globalEntityList[i].CoSpecialBehaviour.type1 = 1;
            globalEntityList[i].color = MAGENTA;
            globalEntityList[i].CoSpecialBehaviour.type1Radius = radius;
        } else if (type == 2)
        {
            globalEntityList[i].CoSpecialBehaviour.type2 = 1;
        }
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

        if (globalEntityList[i].CoSpecialBehaviour.type1 == 1)
        {
            DrawCircleLines(globalEntityList[i].CoPosition.x+5, globalEntityList[i].CoPosition.y+5, globalEntityList[i].CoSpecialBehaviour.type1Radius, GOLD);
        }

    }
}

void SyDetectPlayerCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius)
{

    // Collecting player position

    int playerX = globalEntityList[0].CoPosition.x;
    int playerY = globalEntityList[0].CoPosition.y;

    for (int i = 1; i <= entityCounter; i++)
    {

        if ((abs(playerX - globalEntityList[i].CoPosition.x) < radius) && (abs(playerY - globalEntityList[i].CoPosition.y) < radius))
        {
            // SyEndGame()
            globalEntityList[i].color = RED;
        }
    }
}



// void SyRenderCollisionCircle