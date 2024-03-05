#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "game.h"
// Variables definition

// Main dynamic game variables
int exitGame = 0;
state gameState = MENU;
// state gameState = GAME;
int gameLost = 0;
int spacePoitns = 0;
float gravityAcceleration = 2.0f;

// game object variables

int SyLoadEntitiesCounter;
int specialEntityFirstId;

EnEntity player[1];
int playerAmount = 1;
int playerId;

EnEntity redMeteors[25];
int redMeteorsAmount = sizeof(redMeteors)/sizeof(redMeteors[0]);
int redMeteorsId;

EnEntity greenMeteors[3];
int greenMeteorsAmount = sizeof(greenMeteors)/sizeof(greenMeteors[0]);
int greenMeteorsId;

Texture2D globalTextureList[10];

EnEntity globalEntityList[300];

float speedX = 0.0f;
float speedY = 0.0f;

float scrollingBack = 0.0f;

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
    xmin = 200;
    ymin = 0;
    xmax = screenWidth - 30;
    ymax = screenHeight;

    for (int i = 0; i < entityCounter; i++)
    {

        x = xmin + rand() % (xmax - xmin + 1);
        y = ymin + rand() % (ymax - ymin + 1);

        globalEntityList[i].id = i;
        globalEntityList[i].color = WHITE;
        globalEntityList[i].collision.circleColor = WHITE;
        globalEntityList[i].position.status = 1;
        globalEntityList[i].position.x = x;
        globalEntityList[i].position.y = y;
        globalEntityList[i].collision.centerX = x + (113/2);
        globalEntityList[i].collision.centerY = y + (113/2);
    }

}

// Entity initialiser based on entity type.
int specialEntityFirstId = 0;
void SyInitializeSpecialEntity (EnEntity *globalEntityList, int specialEntityFirstId, int specialEntityCounter, int type, int radius)
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
            globalEntityList[i].collision.circleRadius = 50;   

        } else if (type == 2)
        {
            globalEntityList[i].type.type = 2;
            globalEntityList[i].color = GREEN;
            globalEntityList[i].collision.circleRadius = radius;            
            
        }
    }
}

// Placement related functions 

void SyGravity(EnEntity *globalEntityList, int entityCounter, float gravityAcceleration)
{

    for (int i = 1; i <= entityCounter;i++)
    {
        globalEntityList[i].position.x -= gravityAcceleration;
        
    }
}

void SyUpdateTextureCenter(EnEntity *globalEntityList, int entityCounter)
{

    for (int i = 1; i <= entityCounter;i++)
    {
        globalEntityList[i].collision.centerX = globalEntityList[i].position.x + (113/2);
        globalEntityList[i].collision.centerY = globalEntityList[i].position.y + (113/2);
        
    }

}

void SyResetPosition(EnEntity *globalEntityList, int entityCounter, int screenWidth, int screenHeight)
{
        srand(time(NULL));
        int y,ymin,ymax;
        ymin = 0;
        ymax = screenHeight;

        
    for (int i = 1; i <= entityCounter; i++)
    {
        if (globalEntityList[i].position.x <= 0)
        {
            y = ymin + rand() % (ymax - ymin + 1);

            globalEntityList[i].position.x = screenWidth;
            globalEntityList[i].position.y = y;
            globalEntityList[i].collision.centerX = screenWidth + (113/2);
            globalEntityList[i].collision.centerY = y + (113/2);
            
            switch(globalEntityList[i].type.type)
            {

                case 0:
                    globalEntityList[i].color = GOLD;
                    break;
                case 1:
                    globalEntityList[i].color = RED;
                    break;
                case 2:
                    globalEntityList[i].color = GREEN;
                    globalEntityList[i].collision.circleColor = WHITE;
                    break;
            
            }

        }
    }
}

void SyRenderEntity(EnEntity *globalEntityList, int specialEntityFirstId, int specialEntityCounter, int type, Texture2D *texture, int textureNumber)
{
    for (int i = specialEntityFirstId; i < specialEntityFirstId+specialEntityCounter; i++)
    {
        DrawTexture(texture[textureNumber],globalEntityList[i].position.x, globalEntityList[i].position.y, globalEntityList[i].color);
        if (globalEntityList[i].type.type != 0) 
        {

            DrawCircleLines(globalEntityList[i].collision.centerX, globalEntityList[i].collision.centerY, 113/2, WHITE);
        }
        if (globalEntityList[i].type.type == 2) 
        {
            DrawCircleLines(globalEntityList[i].collision.centerX, globalEntityList[i].collision.centerY, globalEntityList[i].collision.circleRadius, globalEntityList[i].collision.circleColor);
        }
    }
}

void SyDetectPlayerCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius, int *gameLost, int playerTextureWidth, int playerTextureHeight)
{

    // Collecting player position 
    
    // Setting up the central point of the player texture as a reference point for collision - using full texture diameter as we need to flag collision when circle lines overlay 

    int playerX = globalEntityList[0].position.x + (playerTextureWidth/2);
    int playerY = globalEntityList[0].position.y + (playerTextureHeight/2);

    for (int i = 1; i < entityCounter; i++)
    {

        // calculate collision triangle hypotenuse
        int dxSq = pow((abs(playerX - globalEntityList[i].collision.centerX)),2);
        int dySq = pow((abs(playerY - globalEntityList[i].collision.centerY)),2);            
        int entitiesHyp = sqrt(dxSq+dySq);

        // calculate player ship collision circle radius
        int playerHyp = sqrt(pow(65/2,2)+pow(65/2,2));

        if (entitiesHyp<=(globalEntityList[i].collision.circleRadius+playerHyp))
        {
            if (globalEntityList[i].type.type != 2)
            {
                *gameLost = 1;
            }
            // globalEntityList[i].collision.status = 1;
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

void SyMoveSingleEntity(EnEntity *globalEntityList, int entityId, float *speedX, int screenWidth, int screenHeight) 
{
    float speedY;
    if (((IsKeyDown(KEY_RIGHT))||(IsKeyDown(KEY_LEFT))||(IsKeyDown(KEY_DOWN))||(IsKeyDown(KEY_UP))))
    {
        (*speedX)+=0.25;
        speedY = speed(*speedX);
    } 
    
    if (((IsKeyDown(KEY_RIGHT))||(IsKeyDown(KEY_LEFT))||(IsKeyDown(KEY_DOWN))||(IsKeyDown(KEY_UP)))&&(*speedX)>=30)
    {
        if (!((*speedX) < 0))  
        {
            (*speedX) = 30;
        }
    
    }

    if (!((globalEntityList[entityId].position.x > screenWidth+15)||(globalEntityList[entityId].position.x < -15)||(globalEntityList[entityId].position.y > screenHeight+15)||(globalEntityList[entityId].position.y < -50)))
    {
        if (IsKeyDown(KEY_RIGHT))
        {
            globalEntityList[entityId].position.x += GetFrameTime()*speedY;
        } else if (IsKeyDown(KEY_LEFT))
        {
            globalEntityList[entityId].position.x -=  GetFrameTime()*speedY;
        } else if (IsKeyDown(KEY_UP))
        {
            globalEntityList[entityId].position.y -= GetFrameTime()*speedY;
        } else if (IsKeyDown(KEY_DOWN))
        {
            globalEntityList[entityId].position.y +=  GetFrameTime()*speedY;
        } else 
        {
            if (!((*speedX) <= 10))  
            {
                *speedX -= 0.85;
            }
        }

    } else 
    {
        // gameover
    }

   
}


void SyDetectCircleCollision(EnEntity *globalEntityList, int entityCounter, int radius, float *gravityAcceleration)
{
    

    int playerX = globalEntityList[0].position.x + 65/2;
    int playerY = globalEntityList[0].position.y + 65/2;


    for (int i = 1; i < entityCounter; i++)
    {
        if ((globalEntityList[i].type.type == 2) && ((*gravityAcceleration) < 20))
        {
            // calculate collision triangle hypotenuse
            int dxSq = pow((abs(playerX - globalEntityList[i].collision.centerX)),2);
            int dySq = pow((abs(playerY - globalEntityList[i].collision.centerY)),2);            
            int entitiesHyp = sqrt(dxSq+dySq);

            // calculate player ship collision circle radius
            int playerHyp = sqrt(pow(65/2,2)+pow(65/2,2));

            if (entitiesHyp<=(globalEntityList[i].collision.circleRadius+playerHyp))
            {
                globalEntityList[i].collision.circleColor = GREEN;
                (*gravityAcceleration)+=0.1f;

            }
        }
    }

}

float speed(float x)
{
    if (x <= 2.5){
        return abs((x*x*x*x)*2); 
    }
     else 
    {
        return abs((x*x)/1.5); 
    }
}
