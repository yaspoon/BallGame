#ifndef EVENTCOLLISION_H
#define EVENTCOLLISION_H

#include "CollisionEntity.h"

class EventCollision
{
    public:
        EventCollision();
        EventCollision(CollisionEntity *sendTo, CollisionEntity *collider, CollisionResult result);
        virtual ~EventCollision();
        CollisionEntity *getCollider();
        void sendToObject();

    protected:
    private:
        CollisionEntity *collider;
        CollisionEntity *sendTo; //The object to send the event to
        CollisionResult result; //The result of the collision;

};

#endif // EVENTCOLLISION_H
