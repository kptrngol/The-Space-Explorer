#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

// Variables definition
int gameLost = 0;

int gravityAcceleration = 1;


int SyLoadEntitiesCounter;
int specialEntityFirstId;

EnEntity player[1];
int playerAmount = 1;
int playerId;

EnEntity redMeteors[10];
int redMeteorsAmount = sizeof(redMeteors)/sizeof(redMeteors[0]);
int redMeteorsId;

EnEntity greenMeteors[5];
int greenMeteorsAmount = sizeof(greenMeteors)/sizeof(greenMeteors[0]);
int greenMeteorsId;

Texture2D globalTextureList[10];

EnEntity globalEntityList[300];

// Functions initialization


int entitiesNumber = 0;
int SyLoadEntities(EnEntity *source, int sourceSize, EnEntity *target, int targetSize, int *lastElementCounter)
{
    int entitiesBatchId = *lastElementCounter;
    if ((*lastElementCounter) + sourceSize > targetSize)
    {
        printf("Exceeded the maximum set number of entities");
        return 0;
    } else {

        for (int i = (*lastElementCounter); i < sourceSize; i++)
        {
            target[i] = source[i];
        }
        *lastElementCounter += sourceSize; 
    }
    return entitiesBatchId;

}

// Assign components initial values + random position
void SyInitializeEntity(EnEntity *globalEntityList, int entityCounter, int screenWidth, int screenHeight)
{
    srand(time(NULL));
    int x,y,xmin,xmax,ymin,ymax;
    xmin = 60;
    ymin = 0;
    xmax = screenWidth - 30;
    ymax = screenHeight;

    for (int i = 0; i < entityCounter; i++)
    {

        x = xmin + rand() % (xmax - xmin + 1);
        y = ymin + rand() % (ymax - ymin + 1);

        globalEntityList[i].id = i;
        globalEntityList[i].color = WHITE;
        globalEntityList[i].position.status = 1;
        globalEntityList[i].position.x = x;
        globalEntityList[i].position.y = y;
    }

}

// Entity initialiser based on entity type.
int specialEntityFirstId = 0;
void SyInitializeSpecialEntity (EnEntity *globalEntityList, int entityCounter, int specialEntityFirstId, int specialEntityCounter, int type, int radius)
{
    for (int i = specialEntityFirstId; i < specialEntityFirstId+specialEntityCounter; i++)
    {   
        if(type == 0) {
            globalEntityList[i].type.type = 0;
            globalEntityList[i].color = GOLD;
        }
        else if (type == 1)
        {
            globalEntityList[i].type.type = 1;
            globalEntityList[i].color = RED;
            globalEntityList[i].collision.circleRadius = radius;

        } else if (type == 2)
        {
            globalEntityList[i].collision.circleRadius = radius;            
            globalEntityList[i].type.type = 2;
            
        }
    }
}

// Placement related functions 

void SyGravity(EnEntity *globalEntityList, int entityCounter, int gravityAcceleration)
{

    for (int i = 1; i <= entityCounter;i++)
    {
        globalEntityList[i].position.y += gravityAcceleration;
    }

}

void SyResetPosition(EnEntity *globalEntityList, int entityCounter, int screenWidth, int screenHeight)
{
        srand(time(NULL));
        int x,xmin,xmax;
        xmin = 60;
        xmax = screenWidth - 30;

        
    for (int i = 1; i <= entityCounter; i++)
    {
        if (globalEntityList[i].position.y >= screenHeight)
        {
            x = xmin + rand() % (xmax - xmin + 1);

            globalEntityList[i].position.x = x;
            globalEntityList[i].position.y = 0;
            globalEntityList[i].color = WHITE;

        }
    }
}

void SyRenderEntity(EnEntity *globalEntityList, int specialEntityFirstId, int specialEntityCounter, int type, Texture2D texture, int textureNumber)
{
    for (int i = specialEntityFirstId; i < specialEntityFirstId+specialEntityCounter; i++)
    {
        DrawTexture(texture,globalEntityList[i].position.x, globalEntityList[i].position.y, globalEntityList[i].color);
    }
}

void SyDetectPlayerCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius)
{

    // Collecting player position

    int playerX = globalEntityList[0].position.x;
    int playerY = globalEntityList[0].position.y;

    for (int i = 1; i <= entityCounter; i++)
    {

        if ((abs(playerX - globalEntityList[i].position.x) < radius) && (abs(playerY - globalEntityList[i].position.y) < radius))
        {
            // SyEndGame()
            globalEntityList[i].collision.status = 1;
            globalEntityList[i].color = BLACK;
        }
    }
}

// Single entity tools (color, position, assign controls)

void SyColorSingleEntity(EnEntity *globalEntityList, int entityId,Color ChoosenColor)
{
    globalEntityList[entityId].color = ChoosenColor;

}

void SyPositionSingleEntity(EnEntity *globalEntityList, int entityId, int x, int y)
{
    globalEntityList[entityId].position.status = 1;
    globalEntityList[entityId].position.x = x;
    globalEntityList[entityId].position.y = y;

}

void SyMoveSingleEntity(EnEntity *globalEntityList, int entityId, int speed) 
{

    if (IsKeyDown(KEY_RIGHT))
    {
        globalEntityList[entityId].position.x += GetFrameTime()*speed;
    } 

    if (IsKeyDown(KEY_LEFT))
    {
        globalEntityList[entityId].position.x -=  GetFrameTime()*speed;
    }


    if (IsKeyDown(KEY_UP))
    {
        globalEntityList[entityId].position.y -= GetFrameTime()*speed;
    } 

    if (IsKeyDown(KEY_DOWN))
    {
        globalEntityList[entityId].position.y +=  GetFrameTime()*speed;
    }
   
}

void SyDetectCircleCollision(EnEntity *globalEntityList, int entityCounter, int radius, int *gravityAcceleration)
{

    // int playerX = globalEntityList[0].position.x;
    // int playerY = globalEntityList[0].position.y;

    // for (int i = ++playerId; i <= entityCounter; i++)
    // {
    //     // if (globalEntityList[i].type.type == 2)
    //     // {
    //         if ((abs(playerX - globalEntityList[i].position.x) < globalEntityList[i].collision.circleRadius) && (abs(playerY - globalEntityList[i].position.y) < globalEntityList[i].collision.circleRadius))
    //         {
    //             (*gravityAcceleration)+100;
    //         }
    //     // }

    // }

    // Collecting player position

    int playerX = globalEntityList[0].position.x;
    int playerY = globalEntityList[0].position.y;

    for (int i = 1; i <= entityCounter; i++)
    {

        if ((abs(playerX - globalEntityList[i].position.x) < radius) && (abs(playerY - globalEntityList[i].position.y) < radius))
        {
            (*gravityAcceleration)+=10;

        }
    }




}
    


// void SyResetCollisionStatus(EnEntity *globalEntityList, int entityCounter)
// {
//     for (int i = 1; i <= entityCounter; i++)
//     {
//         globalEntityList[i].collision.status = 0;
//         globalEntityList[i].color = GREEN;
//     }
// }
