#ifndef GAME_H
#define GAME_H

// Declare components

typedef struct CoPosition
{
    int status;
    int x;
    int y;
}CoPosition;


typedef struct CoSpecialBehaviour
{
    int type1;
    int type2;
    int type1Radius;

}CoSpecialBehaviour;

// Declare entities

typedef struct EnEntity 
{
    int id;
    Color color;
    CoPosition CoPosition;
    CoSpecialBehaviour CoSpecialBehaviour;
}EnEntity;


// Declare functions

 

void SyInitializeEntity(EnEntity *globalEntityList, int entityCounter);
void SyInitializeSpecialEntity (EnEntity *globalEntityList, int entityCounter, int specialEntityFirstId, int specialEntityCounter, int type, int radius);
void SyPositionSingleEntity(EnEntity *globalEntityList, int entityId, int x, int y);
void SyColorSingleEntity(EnEntity *globalEntityList, int entityId,Color ChoosenColor);
void SyMoveSingleEntity(EnEntity *globalEntityList, int entityId);
void SyRenderEntity(EnEntity *globalEntityList, int entityCounter);
void SyGravity(EnEntity *globalEntityList, int entityCounter);
void SyResetPosition(EnEntity *globalEntityList, int entityCounter, int screenHeight);
void SyDetectPlayerCollision(EnEntity *globalEntityList, EnEntity *additionalEntityList, int entityCounter, int radius);



#endif