#ifndef GAME_H
#define GAME_H

#define COOLDOWNTIME 1

// Declare components

typedef enum State
{
    MENU,
    GAME,
    GAMEOVER
}state;


typedef struct CoPosition
{
    int status;
    int x;
    int y;
}CoPosition;

typedef struct CoCollision
{
    int status;
    int circle;
    int centerX;
    int centerY;
    Color circleColor;
    int circleRadius;
}CoCollision;

typedef struct CoType
{
    int status;
    int type;
    int typeAmount;

}CoType;

typedef struct CoTexture
{
    int status;
    Texture2D texture;
}CoTexture;


// Declare entities

typedef struct EnEntity 
{
    int id;
    CoTexture texture;
    CoPosition position;
    CoCollision collision;
    Color color;
    CoType type;
}EnEntity;


// Declare variables
// Main dynamic game variables
extern int exitGame;
extern state gameState;
extern int gameLost;
extern int spacePoitns;
extern float gravityAcceleration;
extern int collisionCooldownStatus;
extern float collisionCooldownTimer;

extern int SyLoadEntitiesCounter;
extern int specialEntityFirstId;
extern EnEntity player[1];
extern EnEntity redMeteors[25];
extern EnEntity greenMeteors[3];
extern EnEntity globalEntityList[300];
extern int playerAmount;
extern int redMeteorsAmount;
extern int greenMeteorsAmount;
extern int entitiesNumber;
extern int playerId;
extern int redMeteorsId;
extern int greenMeteorsId;
extern Texture2D globalTextureList[10];

extern float speedX;
extern float speedY;

extern float scrollingBack;
// Declare functions
 
int SyLoadEntities(EnEntity *source, int sourceSize, EnEntity *target, int targetSize, int *lastElementCounter);
void SyAssignTextures(EnEntity *globalEntityList, int entityCounter);
void SyInitializeEntity(EnEntity *globalEntityList, int entityCounter, int screenWidth, int screenHeight);
void SyInitializeSpecialEntity (EnEntity *globalEntityList, int specialEntityFirstId, int specialEntityCounter, int type, int radius);
void SyPositionSingleEntity(EnEntity *globalEntityList, int entityId, int x, int y);
void SyColorSingleEntity(EnEntity *globalEntityList, int entityId,Color ChoosenColor);
void SyMoveSingleEntity(EnEntity *globalEntityList, int entityId, float *speedX, int screenWidth, int screenHeight);
void SyRenderEntity(EnEntity *globalEntityList, int specialEntityFirstId, int specialEntityCounter, int type, Texture2D *texture, int textureNumber);
void SyGravity(EnEntity *globalEntityList, int entityCounter, float gravityAcceleration);
void SyUpdateTextureCenter(EnEntity *globalEntityList, int entityCounter);
void SyResetPosition(EnEntity *globalEntityList, int entityCounter, int screenWidth, int screenHeight);
// void SyResetCollisionStatus(EnEntity *globalEntityList, int entityCounter);
void SyDetectPlayerCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius, int *gameLost, int playerTextureWidth, int playerTextureHeight);
void SyCooldownUpdate();
void SyDetectCircleCollision(EnEntity *globalEntityList, int entityCounter, int radius, float *gravityAcceleration);

float speed(float x);

#endif