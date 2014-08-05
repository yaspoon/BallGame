#include "Block.h"

//--------------------------------------Constructors/
Block::Block()
:CollisionEntity()
{
    CollisionEntity::setCtype( C_IMMOVABLE);
}

Block::Block(int width, int height, float x, float y, LAYER drawingLayer)
:CollisionEntity( "./images/block.bmp", x, y, width, height, drawingLayer)
{
    CollisionEntity::setCtype( C_IMMOVABLE );
}

Block::Block(int width, int height, float x, float y, LAYER drawingLayer, CollisionShape shape)
:CollisionEntity( "./images/block.bmp", x, y, width, height, drawingLayer, CS_AABB, shape)
{
    CollisionEntity::setCtype( C_IMMOVABLE );
}

Block::Block(std::string filePath, int width, int height, float x, float y, LAYER drawingLayer)
:CollisionEntity(filePath, x, y, width, height, drawingLayer)
{
    CollisionEntity::setCtype( C_IMMOVABLE );
}

Block::Block(std::string filePath, int width, int height, float x, float y, LAYER drawingLayer, CollisionShape shape)
:CollisionEntity(filePath, x, y, width, height, drawingLayer, CS_AABB, shape)
{
    CollisionEntity::setCtype( C_IMMOVABLE );
}
//--------------------------------------Destructors/
Block::~Block()
{

}

void Block::handleInputEvent(EventInput input)
{
    switch(input.getType())
    {
        case EV_INPUT_KEYDOWN:
        case EV_INPUT_KEYUP:
        case EV_INPUT_UNKNOWN:
        default:
            break;

    }
}

void Block::handleSystemEvent(EventSystem system)
{
    switch(system.getType())
    {
        case EV_SYS_QUIT:
        case EV_SYS_UNKNOWN:
        default:
            break;
    }
}

void Block::handleCollisionEvent(CollisionEntity *collision, CollisionResult result)
{
    collision = NULL;
}

CollisionEntity *Block::clone()
{
    Block *tmp = new Block(*this);
    return (CollisionEntity*)tmp;
}
