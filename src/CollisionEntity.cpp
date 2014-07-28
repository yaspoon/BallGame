#include "CollisionEntity.h"

CollisionEntity::CollisionEntity()
:VisualEntity()
{
        xvel = 0;
        yvel = 0;
}

CollisionEntity::CollisionEntity(std::string filename, float x, float y, float width, float height)
:VisualEntity(filename, x, y, width, height)
{
    xvel = 0;
    yvel = 0;
}

CollisionEntity::~CollisionEntity()
{
    //dtor
}

float CollisionEntity::getXvel()
{
    return xvel;
}

float CollisionEntity::getYvel()
{
    return yvel;
}

void CollisionEntity::setXvel(float newVel)
{
    xvel = newVel;
}

void CollisionEntity::setYvel(float newVel)
{
    yvel = newVel;
}
