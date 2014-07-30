#include "EventCollision.h"

EventCollision::EventCollision()
{
    collider = NULL;
}

EventCollision::EventCollision(CollisionEntity *collider)
{
    this->collider = collider->clone();
}

EventCollision::~EventCollision()
{
    delete collider;
}

CollisionEntity *EventCollision::getCollider()
{
    return collider;
}
