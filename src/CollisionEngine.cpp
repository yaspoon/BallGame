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
                CollisionResult collisionResult = testForCollision(collider1, collider2);
                if(collisionResult.isColliding) //If they're colliding
                {
                    if(collider1->getCtype() == C_MOVEABLE) //If this thing is allowed to move we can push it out
                    {
                        if(collider2->getCtype() == C_MOVEABLE) //If they both can move maybe we can push both of them out of colliding
                        {
                            Rect collider1pos = collider1->getPosDim();
                            collider1pos.x = collider1pos.x + (collisionResult.minAxis.x * (collisionResult.minDistance / 2));
                            collider1pos.y = collider1pos.y + (collisionResult.minAxis.y * (collisionResult.minDistance / 2));
                            collider1->setPos(collider1pos.x, collider1pos.y);

                            Rect collider2pos = collider2->getPosDim();
                            collider2pos.x = collider2pos.x - (collisionResult.minAxis.x * (collisionResult.minDistance / 2));
                            collider2pos.y = collider2pos.y - (collisionResult.minAxis.y * (collisionResult.minDistance / 2));
                            collider2->setPos(collider2pos.x, collider2pos.y);
                         }
                        else //Nope just move collider1 out then
                        {
                            Rect posDim = collider1->getPosDim();
                            posDim.x = posDim.x + (collisionResult.minAxis.x * collisionResult.minDistance);
                            posDim.y = posDim.y + (collisionResult.minAxis.y * collisionResult.minDistance);
                            collider1->setPos(posDim.x, posDim.y);
                        }
                    }
                    else if(collider2->getCtype() == C_MOVEABLE) //Well I hope this object can move else we can't do fuck all about them colliding
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
    CollisionResult retval = {true, {0, 0}, 0};
    retval.minDistance = 1000.0f;

    std::vector<vec2> collider1Axes = collider1->getNormedAxes();
    std::vector<vec2>::iterator it = collider1Axes.begin();
    while(retval.isColliding && it != collider1Axes.end())
    {
        /*Project each vertex of the two colliders onto the axis and then
         *check them for overlap*/
        std::vector<float> collider1Points = collider1->minMaxProjectOnto(*it);
        std::vector<float> collider2Points = collider2->minMaxProjectOnto(*it);
        CollisionResult overlaping = checkForOverlap(collider1Points, collider2Points);
        if(!overlaping.isColliding) //If there is no overlap then stop
        {
            retval.isColliding = false;
        }
        else //Yes they're overlaping on this axis
        {
            //Check if this is the smallest distance we have found so far
            if(fabs(overlaping.minDistance) < fabs(retval.minDistance))
            {
                retval.minDistance = overlaping.minDistance;
                retval.minAxis = *it;
            }
        }

        ++it;
    }

    //If they weren't overlaping on the first set of axes then no point testing this axes
    if(retval.isColliding)
    {
        std::vector<vec2> collider2Axes = collider2->getNormedAxes();
        std::vector<vec2>::iterator it = collider2Axes.begin();
        while(retval.isColliding && it != collider2Axes.end())
        {
            /*Project each of the colliders vertices onto the axes
             *of collider2*/
             std::vector<float> collider1Points = collider1->minMaxProjectOnto(*it);
             std::vector<float> collider2Points = collider2->minMaxProjectOnto(*it);
            CollisionResult overlaping = checkForOverlap(collider1Points, collider2Points);
            if(!overlaping.isColliding) //if not overlaping then stop
            {
                retval.isColliding = false;
            }
            else //There is overlap
            {
                //Check if this is the smallest distance so far
                if(fabs(overlaping.minDistance) < fabs(retval.minDistance))
                {
                    retval.minDistance = overlaping.minDistance;
                    retval.minAxis = *it;
                }
            }
            ++it;
        }
    }

    return retval;
}

CollisionResult CollisionEngine::checkForOverlap(std::vector<float> collider1Points, std::vector<float> collider2Points)
{
    CollisionResult retval = {false, {0,0}, 0};

    return retval;
}

/*
    bool isInside(vec2 point, Rect rectangle) //See if point is inside the rectangles boundary
    {
        bool retval = false;

        if(point.x >= rectangle.x && point.x <= (rectangle.x + rectangle.w))
        {
                if(point.y >= rectangle.y && point.y <= (rectangle.y + rectangle.h))
                {
                    retval = true;
                }
        }

        return retval;
    }

    bool isColliding(Rect collider1, Rect collider2)
    {
        STUB("Vec2 is changing so this won't work no more");
        bool retval = false;

        vec2 topLeft = {collider1.x, collider1.y};
        if(isInside(topLeft, collider2) == true)
        {
            retval = true;
        }

        vec2 topRight = {collider1.x + collider1.w, collider1.y};
        if(isInside(topRight, collider2))
        {
            retval = true;
        }

        vec2 bottomLeft = {collider1.x, collider1.y + collider1.h};
        if(isInside(bottomLeft, collider2))
        {
            retval = true;
        }

        vec2 bottomRight = {collider1.x + collider1.w, collider1.y + collider1.h};
        if(isInside(bottomRight, collider2))
        {
            retval = true;
        }

        return retval;
    }

    void BallGame::checkCollisions()
    {
        STUB("So very many pointers to remove...");
        BOOST_FOREACH( Entity entity, entities )
        {
            VisualEntity collidee = entity;

            BOOST_FOREACH(Entity colliders, entities )
            {
                VisualEntity collider = colliders;
                if( collidee != collider && collidee.getCtype() != C_IMMOVABLE)
                {
                    //if(isColliding(collidee->getPosDim(), collider->getPosDim())) // No point in doing collision detection if they're not even colliding...
                    {
                        Collision_t ret;
                        if(collide( collidee, collider, &ret) == true)
                        {
                            std::cout << "The objects are colliding" << std::endl;

                            if(collidee.getCtype() == C_MOVEABLE && collider.getCtype() == C_MOVEABLE) //They can both move so push both back half the vector
                            {
                                std::cout << "Both can move" << std::endl;
                            }
                            else if(collidee.getCtype() == C_MOVEABLE && collider.getCtype() == C_IMMOVABLE)
                            {
                                Rect position = collidee->getPosDim();
                                position.x = (int)(position.x + (ret.axes.x * ret.overlap));
                                position.y = (int)(position.y + (ret.axes.y * ret.overlap));

                                collidee->setPos(position.x, position.y);
                                Player *tmp = dynamic_cast<Player*>(collidee);
                                if(ret.axes.y > 0)
                                {
                                    if(ret.overlap < 0)
                                    {
                                        tmp->setYvel(0.0f);
                                        tmp->onGround = true;
                                    }
                                    else if( ret.overlap > 0)
                                    {
                                        float yvel = tmp->getYvel();
                                        tmp->setYvel((-yvel)/2);
                                    }
                                }
                            }
                            else if(collidee->getCtype() == C_IMMOVABLE && collider->getCtype() == C_MOVEABLE)
                            {
                                std::cout << "This should happen" << std::endl;
                            }
                        }
                    }
                }
            }
            checkBounds( collidee );
        }
    }

void minMax(std::vector<float> points, float *min, float *max)
{
    std::vector<float>::iterator it = points.begin();
    *min = *it;
    *max = *it;

    for(++it; it != points.end(); ++it)
    {
        if(*it < *min)
        {
            *min = *it;
        }

        if(*it > *max)
        {
            *max = *it;
        }
    }
}

bool checkContainment(float minCollidee, float maxCollidee, float minCollider, float maxCollider)
{
    bool retval = false;

    if((minCollider <= minCollidee && minCollidee <= maxCollider) && (minCollider <= maxCollidee && maxCollidee <= maxCollider))
    {
            retval = true;
    }

    return retval;
}

bool overlap(float minCollidee, float maxCollidee, float minCollider, float maxCollider, float *amountOverlap)
{
    bool overlap = false;

    float aminCollidee = fabs(minCollidee);
    float amaxCollidee = fabs(maxCollidee);
    if(amaxCollidee < aminCollidee)
    {
        float tmp = aminCollidee;
        aminCollidee = amaxCollidee;
        amaxCollidee = tmp;
    }


    float aminCollider = fabs(minCollider);
    float amaxCollider = fabs(maxCollider);
    if(amaxCollider < aminCollider)
    {
        float tmp = aminCollider;
        aminCollider = amaxCollider;
        amaxCollider = tmp;
    }

    if(checkContainment(aminCollidee, amaxCollidee, aminCollider, amaxCollider))
    {
        overlap = true;
        if(fabs(aminCollidee - aminCollider) < fabs(amaxCollider - amaxCollidee))
        {
            *amountOverlap = aminCollider - amaxCollidee;//aminCollider - (aminCollidee + (amaxCollidee - aminCollidee));
        }
        else
        {
            *amountOverlap = amaxCollider - aminCollidee;
        }
    }
    else if(checkContainment(aminCollider, amaxCollider, aminCollidee, amaxCollidee))
    {
        overlap = true;
        if((aminCollider - aminCollidee) < (amaxCollidee - amaxCollider))
        {
            *amountOverlap = aminCollidee - amaxCollider;
        }
        else
        {
            *amountOverlap = amaxCollidee - aminCollider;
        }
    }
    else if((aminCollider <= aminCollidee && aminCollidee <= amaxCollider))
    {
        overlap = true;
        float minCollideeMinCollider = fabs(minCollidee - minCollider);
        float minCollideeMaxCollider = fabs(minCollidee - maxCollider);

        *amountOverlap = min(minCollideeMinCollider, minCollideeMaxCollider);
    }
    else if((aminCollider <= amaxCollidee && amaxCollidee <= amaxCollider))
    {
        overlap = true;
        float maxCollideeMinCollider = fabs(maxCollidee - minCollider);
        float maxCollideeMaxCollider = fabs(maxCollidee - maxCollider);

        float tmp = min(maxCollideeMinCollider, maxCollideeMaxCollider);
        *amountOverlap = -tmp;
    }

    return overlap;
}


bool BallGame::collide( VisualEntity collidee, VisualEntity collider, Collision_t *collision)
{
    STUB("The collide needs to be rewritten to get rid of all the damn pointers now");

    bool colliding = true;
    std::vector<vec2> axes = collidee->getNormedAxes();

    vec2 minAxis;
    int minOverlap = 1000;//std::numeric_limits<float>::max();

    for(std::vector<vec2>::iterator it = axes.begin(); it != axes.end(); ++it)
    {
        vec2 axis = *it;

        std::vector<float> projection1 = collidee->projectOnto(axis);
        std::vector<float> projection2 = collider->projectOnto(axis);

        float proj1Min;
        float proj1Max;

        minMax(projection1, &proj1Min, &proj1Max);

        float proj2Min;
        float proj2Max;

        minMax(projection2, &proj2Min, &proj2Max);

        float amountOverlap = 0.0f;

        if(overlap(proj1Min, proj1Max, proj2Min, proj2Max, &amountOverlap) == true)
        {
            if(fabs(amountOverlap) < fabs(minOverlap))
            {
                minOverlap = amountOverlap;
                minAxis = axis;
            }
        }
        else
        {
            colliding = false;
        }

    }

    collision->axes = minAxis;
    collision->overlap = minOverlap;

    return colliding;
}*/
