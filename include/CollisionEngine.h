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
        CollisionResult checkForOverlap(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
        bool isInside(float point, std::pair<float,float> points);
        bool isContained(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
        float distanceBetween(float firstPoint, float secondPoint);
        bool isColliding(Rect collider1, Rect collider2);
        bool isInside2(vec2 point, Rect rectangle);
};

#endif // COLLISIONENGINE_H
