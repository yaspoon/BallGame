#include "BallGame.h"
#include "CollisionEntity.h"

CollisionEntity::CollisionEntity()
:VisualEntity()
{
        BALLGAME.getCurrentLevel()->addCollidableObject(this);
        xvel = 0;
        yvel = 0;
        onGround = false;
}

CollisionEntity::CollisionEntity(std::string filename, float x, float y, float width, float height)
:VisualEntity(filename, x, y, width, height)
{
    BALLGAME.getCurrentLevel()->addCollidableObject(this);
    xvel = 0;
    yvel = 0;
    onGround = false;
}

CollisionEntity::~CollisionEntity()
{
    BALLGAME.getCurrentLevel()->removeCollidableObject(this);
}

float CollisionEntity::getXvel()
{
    return xvel;
}

float CollisionEntity::getYvel()
{
    return yvel;
}

bool CollisionEntity::getOnGround()
{
    return onGround;
}

COLLIDABLE CollisionEntity::getCtype()
{
    return cType;
}

void CollisionEntity::setXvel(float newVel)
{
    xvel = newVel;
}

void CollisionEntity::setYvel(float newVel)
{
    yvel = newVel;
}

void CollisionEntity::setOnGround(bool isOnGround)
{
    onGround = isOnGround;
}

void CollisionEntity::setCtype( COLLIDABLE type )
{
    cType = type;
}
