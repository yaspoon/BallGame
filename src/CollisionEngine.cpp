#include "CollisionEngine.h"
#include <boost/foreach.hpp>

CollisionEngine::CollisionEngine()
{
    //ctor
}

CollisionEngine::~CollisionEngine()
{
    //dtor
}

void CollisionEngine::handleCollisions(std::vector<CollisionEntity*> collidables, std::shared_ptr<EventEngine> eventEngine)
{
    BOOST_FOREACH(CollisionEntity *collider1, collidables)
    {
        BOOST_FOREACH(CollisionEntity *collider2, collidables)
        {
            if(collider1 != collider2) //Not the same object
            {
                //STUB("Collision handling not implemented yet");
                CollisionResult collisionResult = testForCollision(collider1, collider2);
                if(collisionResult.isColliding) //If they're colliding
                {
                    if(collider1->getCtype() == C_MOVEABLE) //If this thing is allowed to move we can push it out
                    {
                        if(collider2->getCtype() == C_MOVEABLE) //If they both can move maybe we can push both of them out of colliding
                        {

                        }
                        else
                        {
                            Rect posDim = collider1->getPosDim();
                            posDim.x = posDim.x + (collisionResult.minAxis.x * collisionResult.minDistance);
                            posDim.y = posDim.y + (collisionResult.minAxis.y * collisionResult.minDistance);
                            collider1->setPos(posDim.x, posDim.y);
                        }
                    }
                    else if(collider2->getCtype() == C_MOVEABLE); //Well I hope this object can move else we can't do fuck all about them colliding
                    {
                        Rect posDim = collider2->getPosDim();
                        posDim.x = posDim.x + (collisionResult.minAxis.x * collisionResult.minDistance);
                        posDim.y = posDim.y + (collisionResult.minAxis.y * collisionResult.minDistance);
                        collider2->setPos(posDim.x, posDim.y);
                    }
                }
            }
        }
    }
}

CollisionResult CollisionEngine::testForCollision(CollisionEntity* collider1, CollisionEntity *collider2)
{
    CollisionResult retval = {false, {0, 0}, 0};
    //STUB("Not implemented yet");
    return retval;
}
