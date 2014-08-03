#include "EventCollision.h"

EventCollision::EventCollision()
{
    collider = NULL;
}

EventCollision::EventCollision(CollisionEntity *sendTo, CollisionEntity *collider, CollisionResult result)
{
    this->sendTo = sendTo;
    this->collider = collider->clone();
    this->result = result;
}

EventCollision::EventCollision(const EventCollision& other)
{
    this->sendTo = other.sendTo;
    this->collider = other.collider->clone();
    this->result = result;
}

EventCollision::~EventCollision()
{
    delete collider;
}

CollisionEntity *EventCollision::getCollider()
{
    return collider;
}

void EventCollision::sendToObject()
{
    sendTo->handleCollisionEvent(collider, result);
}
