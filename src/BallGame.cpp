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
            currentLevel = new Level();
            currentLevel->initialise();
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
                eventHandling();
                /*End of Event Handling*/

                //Make all the game objects update themselves to any changes
                updateFrame();

                collisionEngine.handleCollisions(currentLevel->getmoveableObjects(), currentLevel->getimmoveableObjects(), eventEngine);

                BOOST_FOREACH(CollisionEntity *entity, currentLevel->getmoveableObjects())
                {
                    checkBounds(entity);
                }
                BOOST_FOREACH(CollisionEntity *entity, currentLevel->getimmoveableObjects())
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

    Level *BallGame::getCurrentLevel()
    {
        return currentLevel;
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

void BallGame::checkBounds(CollisionEntity *entity)
{
    //STUB("Needs all the pointers removing");
    SDL_Rect tmp = currentLevel->getLevelDimensions();
    int screenWidth = tmp.w;
    int screenHeight = tmp.h;
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
        entity->setOnGround(true);
        entity->setYvel(0.0f);
    }

    entity->setPos( posDim.x, posDim.y );
}

void BallGame::eventHandling()
{
    eventEngine->processEvents(); //Gather all events and then send them to the respective game objects

    BOOST_FOREACH(EventSystem sysEv, eventEngine->getSystemEvents())
    {
        switch(sysEv.getSystemType())
        {
            case EV_SYS_QUIT:
                quit = true;
                break;
            case EV_SYS_UNKNOWN:
                break;
            default:
                break;
        }
    }

    BOOST_FOREACH(EventInput input, eventEngine->getInputEvents())
    {
        if(input.getType() == EV_INPUT_KEYDOWN)
        {
            switch(input.getKey())
            {
                case KEY_Q:
                    quit = true;
                    break;
                case KEY_F1:
                    renderEngine.toggleFullScreen();
                    break;
            }
        }
    }

    eventEngine->clearEventQueues(); //Clear all the events from the queues ready for next frame
}


