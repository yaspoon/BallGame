#include "BallGame.h"
#include "VisualEntity.h"
#include "Timer.h"
#include <typeinfo>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/foreach.hpp>
#include <math.h>
#include <algorithm>

using namespace std;

//--------------------------------------Private methods/
    void BallGame::handleKeyPress( SDL_Event keyEvents )
    {
        switch( keyEvents.key.keysym.sym )
        {
            case SDLK_LEFT:
                //printf( "Left pressed\n" );
                break;
            case SDLK_RIGHT:
                //printf( "Right pressed\n" );
                break;
            case SDLK_ESCAPE:
            case SDLK_q:
                quit = true;
                break;
            case SDLK_F1:
                std::cout << "NOT IMPLETMENTED" << std::endl;
                break;
            default:
                break;
        }
    }

//--------------------------------------Constructors/
    BallGame::BallGame()
    {
        quit = false;
        resourceManager = std::unique_ptr<ResourceManager>(new ResourceManager());
        eventEngine = std::unique_ptr<EventEngine>(new EventEngine());
        m_gameName = "Simple BallGame";
        frame = 0;


    }

//--------------------------------------Destructors/
    BallGame::~BallGame()
    {

    }

//--------------------------------------Methods/
    int BallGame::ballGameMain()
    {
        if(renderEngine.initialise())
        {
            resourceManager->initialise();
            currentLevel = std::unique_ptr<Level>(new Level());
            Timer fps;
            Timer update;

            update.start();
            lastframe = SDL_GetTicks();

            /*****************************************************
            *           Main Loop
            *
            *****************************************************/
            while( !quit )
            {

                fps.start();
            /*****************************************************
            *           Event Handling
            *
            *****************************************************/
                eventEngine->processEvents();
                BOOST_FOREACH(EventSystem sysEv, eventEngine->getSystemEvents())
                {
                    switch(sysEv.getSystemType())
                    {
                        case EV_SYS_QUIT:
                            quit = true;
                    }
                }

                /*End of Event Handling*/

                //Get all the objects that have added themselves
                proccessAddedObjects();

                //Make all the game objects update themselves to any changes
                updateFrame();

                BOOST_FOREACH(VisualEntity *entity, currentLevel->getDrawableObjects())
                {
                    checkBounds(entity);
                }

                //checkCollisions();

                /*****************************************************
                *            Display
                *
                *****************************************************/
                //Draw all the game objects to the screen
                currentLevel->draw(renderEngine);
                /*End of display*/

                frame++;

                if( update.getTicks() > 1000 )
                {
                    std::stringstream caption;

                    caption << "Average FPS " << frame / ( update.getTicks() / 1000.f );

                    renderEngine.setWindowTitle(caption.str().c_str());

                    update.start();

                    frame = 0;

                }

                /*if( fps.getTicks() < (1000 / FRAMES_PER_SECOND) )
                {
                    SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.getTicks() );
                }*/


            }
            //End Main Game loop

            renderEngine.cleanup(); //Clean up SDL WIndow
            SDL_Quit();
        }
        else
        {
            printf( "Could not initialise sdl exiting error: %s\n", SDL_GetError() );
        }
        return retVal;

    }

    RenderEngine BallGame::getRenderEngine()
    {
        return renderEngine;
    }

    std::shared_ptr<ResourceManager> BallGame::getResourceManager()
    {
        return resourceManager;
    }

    std::shared_ptr<EventEngine> BallGame::getEventEngine()
    {
        return eventEngine;
    }

    void BallGame::proccessAddedObjects()
    {
        BOOST_FOREACH(Entity object, addedEntities)
        {
            STUB("Can't process add entities as that has been moved into level");
            //entities.push_back( object );
        }

        addedEntities.clear();
    }

    void BallGame::proccessRemovedObjects()
    {
        BOOST_FOREACH(Entity entity, removedEntities )
        {
            STUB("Can't remove entities because I commented it out long ago apparently..");
            //entities.erase(std::find(entities.begin(), entities.end(), entity));
        }
    }

    void BallGame::addEntity(Entity entity_i)
    {
        addedEntities.push_back( entity_i );
    }

    void BallGame::removeEntity(Entity entity_i)
    {
        removedEntities.push_back( entity_i );
    }

    void BallGame::updateFrame()
    {
        Uint32 thisframe = SDL_GetTicks();
        float dt = (float)( thisframe - lastframe ) / 1000.f;
        lastframe = thisframe;

        BOOST_FOREACH( Entity *object, currentLevel->getLevelObjects())
        {
            object->update( dt );
        }
    }

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
        /*BOOST_FOREACH( Entity entity, entities )
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
        }*/
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

    /*bool colliding = true;
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

    return colliding;*/
}

void BallGame::checkBounds(VisualEntity *entity)
{
    //STUB("Needs all the pointers removing");
    ScreenDimensions tmp = renderEngine.getScreenDimensions();
    int screenWidth = tmp.width;
    int screenHeight = tmp.height;
    Rect posDim = entity->getPosDim();

    if( posDim.x < 0 )
    {
        posDim.x = 0;
    }
    else if( posDim.x + posDim.w > screenWidth )
    {
        posDim.x = screenWidth - posDim.w;
    }

    if( posDim.y < 0 )
    {
        posDim.y = 0;
    }
    else if( posDim.y + posDim.h > screenHeight )
    {
        posDim.y = screenHeight - posDim.h;
        Player *tmp = dynamic_cast<Player*>(entity);
        tmp->onGround = true;
        tmp->setYvel(0.0f);
    }

    entity->setPos( posDim.x, posDim.y );
}


