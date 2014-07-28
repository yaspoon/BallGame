#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include "CollisionEntity.h"
#include "EventEngine.h"

class CollisionEngine
{
    public:
        CollisionEngine();
        virtual ~CollisionEngine();
        void handleCollisions(std::vector<CollisionEntity*> collidables, std::shared_ptr<EventEngine> eventEngine);
    protected:
    private:
};

#endif // COLLISIONENGINE_H
