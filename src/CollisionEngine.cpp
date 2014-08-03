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

                            if(collisionResult.minAxis.y > 0) //Collison happened on y axis
                            {
                                if(collisionResult.minDistance <= 0.0f)
                                {
                                    collider1->setOnGround(true);
                                    collider1->setYvel(0.0f);
                                }
                                else
                                {
                                    collider1->setYvel(-collider1->getYvel());
                                }

                            }
                        }
                    }
                    else if(collider2->getCtype() == C_MOVEABLE) //Well I hope this object can move else we can't do fuck all about them colliding
                    {
                        Rect posDim = collider2->getPosDim();
                        posDim.x = posDim.x + (collisionResult.minAxis.x * collisionResult.minDistance);
                        posDim.y = posDim.y + (collisionResult.minAxis.y * collisionResult.minDistance);
                        collider2->setPos(posDim.x, posDim.y);
                        if(collisionResult.minAxis.y > 0) //Collison happened on y axis
                        {
                            if(collisionResult.minDistance < 0.0f)
                            {
                                collider2->setOnGround(true);
                                collider2->setYvel(0.0f);
                            }
                            else
                            {
                                collider2->setYvel(-collider2->getYvel());
                            }

                        }
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
        std::pair<float,float> collider1Points = collider1->minMaxProjectOnto(*it);
        std::pair<float,float> collider2Points = collider2->minMaxProjectOnto(*it);
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
             std::pair<float,float> collider1Points = collider1->minMaxProjectOnto(*it);
             std::pair<float,float> collider2Points = collider2->minMaxProjectOnto(*it);
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

CollisionResult CollisionEngine::checkForOverlap(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points)
{
    CollisionResult retval = {false, {0,0}, 0};

    if(isContained(collider1Points, collider2Points)) //Collider1 is completely contained by collider2
    {
        retval.minDistance = calculatePushOut(collider1Points, collider2Points);
        retval.isColliding = true;
    }
    else if(isContained(collider2Points, collider1Points)) //Collider2 is completely contained by collider1
    {
        retval.minDistance = calculatePushOut(collider2Points, collider1Points);
        retval.isColliding = true;
    }
    else if(isInside(collider1Points.first, collider2Points)) //Collider1s min point is inside collider2 so it's on the right
    {

        retval.minDistance = collider2Points.second - collider1Points.first;
        retval.isColliding = true;
    }
    else if(isInside(collider1Points.second, collider2Points)) //Collider1s max point is inside collider2 so it's on the left
    {
        retval.minDistance = collider2Points.first - collider1Points.second;
        retval.isColliding = true;
    }
    /*else they are not overlaping at all*/

    return retval;
}

/*
 *Tests if point is between (inside) the other two points
 */
bool CollisionEngine::isInside(float point, std::pair<float,float> points)
{
    bool retval = false;

    if(points.first < point && point < points.second)
    {
        retval = true;
    }
    else if(points.second < point && point < points.first) //Incase they're all negative
    {
        retval = true;
    }

    return retval;
}

bool CollisionEngine::isContained(std::pair<float,float> collider1Points, std::pair<float,float> collider2Points)
{
    bool retval = false;

    if((isInside(collider1Points.first, collider2Points) || collider1Points.first == collider2Points.first) && (isInside(collider1Points.second, collider2Points) || collider1Points.second == collider2Points.second))
    {
        retval = true;
    }

    return retval;
}

float CollisionEngine::distanceBetween(float firstPoint, float secondPoint)
{
    float retval = 0.0f;

    if(firstPoint < secondPoint)
    {
        retval = secondPoint - firstPoint;
    }
    else
    {
        retval = firstPoint - secondPoint;
    }

    return retval;
}

/*When one object is contained within the other, this calculates how far they must move to push out*/
float CollisionEngine::calculatePushOut(std::pair<float,float> contained, std::pair<float,float> container)
{
    float retval = 0.0f;
    if(distanceBetween(contained.first, container.first) < distanceBetween(contained.second, container.second))
    {
        retval = (container.first - contained.first) - (contained.second - contained.first);
    }
    else
    {
        retval = (container.second - contained.second) + (contained.second - contained.first);
    }

    return retval;
}
