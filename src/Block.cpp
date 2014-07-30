#include "Block.h"

//--------------------------------------Constructors/
Block::Block()
:CollisionEntity("./images/block.bmp", 20.0f, 20.0f, 20.0f, 20.0f )
{
    CollisionEntity::setCtype( C_IMMOVABLE);

}

Block::Block(int width, int height, float x, float y )
:CollisionEntity( "./images/block.bmp", x, y, width, height )
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

void Block::handleCollisionEvent(CollisionEntity *collision)
{
    collision = NULL;
}

CollisionEntity *Block::clone()
{
    Block *tmp = new Block(*this);
    return (CollisionEntity*)tmp;
}
