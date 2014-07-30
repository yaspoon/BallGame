#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include "CollisionEntity.h"
#include "EventEngine.h"
#include "bgCommon.h"
#include <vector>

struct CollisionResult
{
    bool isColliding;
    vec2 minAxis;
    float minDistance;
};

class CollisionEngine
{
    public:
        CollisionEngine();
        virtual ~CollisionEngine();
        void handleCollisions(std::vector<CollisionEntity*> collidables, std::shared_ptr<EventEngine> eventEngine);
        CollisionResult testForCollision(CollisionEntity* collider1, CollisionEntity *collider2);
    protected:
    private:
};

#endif // COLLISIONENGINE_H
