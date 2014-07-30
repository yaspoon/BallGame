#ifndef EVENTCOLLISION_H
#define EVENTCOLLISION_H

#include "CollisionEntity.h"

class EventCollision
{
    public:
        EventCollision();
        EventCollision(CollisionEntity *collider);
        virtual ~EventCollision();
        CollisionEntity *getCollider();
    protected:
    private:
        CollisionEntity *collider;

};

#endif // EVENTCOLLISION_H
