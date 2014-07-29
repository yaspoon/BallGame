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
    STUB("Collision handling not implemented yet");
    BOOST_FOREACH(CollisionEntity *collider1, collidables)
    {
        BOOST_FOREACH(CollisionEntity *collider2, collidables)
        {
            if(collider1 != collider2)
            {

            }
        }
    }
}
