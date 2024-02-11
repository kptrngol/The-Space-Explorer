#ifndef GAME_H
#define GAME_H

// Declare components

typedef struct CoPosition
{
    int status;
    int x;
    int y;
}CoPosition;

typedef struct CoCollision
{
    int status;
}CoCollision;


typedef struct CoSpecialBehaviour
{
    int status;
    int type1;
    int type2;
    int type1Radius;

}CoSpecialBehaviour;

typedef struct CoTexture
{
    int status;
    Texture2D texture;
}CoTexture;

// Declare entities

typedef struct EnEntity 
{
    int id;
    Color color;
    CoPosition position;
    CoSpecialBehaviour specialBehaviour;
    CoCollision collision;
    CoTexture texture;
}EnEntity;

extern int SyLoadEntitiesCounter;
extern int specialEntityFirstId;
extern EnEntity player[1];
extern EnEntity redMeteors[100];
extern EnEntity greenMeteors[100];
extern EnEntity globalEntityList[300];
extern int entitiesNumber;

// Declare functions

 
int SyLoadEntities(EnEntity *source, int sourceSize, EnEntity *target, int targetSize, int *lastElementCounter);
void SyAssignTextures(EnEntity *globalEntityList, int entityCounter);
void SyInitializeEntity(EnEntity *globalEntityList, int entityCounter, int screenWidth, int screenHeight);
void SyInitializeSpecialEntity (EnEntity *globalEntityList, int entityCounter, int specialEntityFirstId, int specialEntityCounter, int type, int radius);
void SyPositionSingleEntity(EnEntity *globalEntityList, int entityId, int x, int y);
void SyColorSingleEntity(EnEntity *globalEntityList, int entityId,Color ChoosenColor);
void SyMoveSingleEntity(EnEntity *globalEntityList, int entityId, int speed);
void SyRenderEntity(EnEntity *globalEntityList, int entityCounter, Texture2D texture);
void SyGravity(EnEntity *globalEntityList, int entityCounter, int gravityAcceleration);
void SyResetPosition(EnEntity *globalEntityList, int entityCounter, int screenHeight);
void SyResetCollisionStatus(EnEntity *globalEntityList, int entityCounter);
void SyDetectPlayerCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius);



#endif