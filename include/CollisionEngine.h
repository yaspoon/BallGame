#ifndef COLLISIONENGINE_H
#define COLLISIONENGINE_H

#include "CollisionEntity.h"
#include "EventEngine.h"
#include "bgCommon.h"
#include <vector>

class CollisionEngine
{
    public:
        CollisionEngine();
        virtual ~CollisionEngine();
        void handleCollisions(std::vector<CollisionEntity*> moveables, std::vector<CollisionEntity*> immoveables, std::shared_ptr<EventEngine> eventEngine);
        CollisionResult testForCollision(CollisionEntity* collider1, CollisionEntity *collider2);
    protected:
    private:
        CollisionResult checkForOverlap(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
        bool isInside(float point, std::pair<float,float> points);
        bool isContained(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
        float distanceBetween(float firstPoint, float secondPoint);
        float calculatePushOut(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points);
};

#endif // COLLISIONENGINE_H
