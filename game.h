#ifndef GAME_H
#define GAME_H

// Declare components

typedef struct CoPosition
{
    int status;
    int x;
    int y;
}CoPosition;

// Declare entities

typedef struct EnEntity 
{
    int id;
    Color color;
    CoPosition CoPosition;
}EnEntity;


// Declare functions

void SyInitializeEntity(EnEntity * globalEntityList, int entityCounter);
void SyPositionSingleEntity(EnEntity * globalEntityList, int entityId, int x, int y);
void SyColorSingleEntity(EnEntity * globalEntityList, int entityId,Color ChoosenColor);
void SyMoveSingleEntity(EnEntity * globalEntityList, int entityId);
void SyRenderEntity(EnEntity * globalEntityList, int entityCounter);
void SyGravity(EnEntity * globalEntityList, int entityCounter);
void SyResetPosition(EnEntity * globalEntityList, int entityCounter, int screenHeight);


#endif