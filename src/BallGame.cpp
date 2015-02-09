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

    static void *runThread(void *data)
    {
        static int count = 0;
        std::cout << "Running thread for the " << count << " time" << std::endl;
        count++;
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
                eventEngine->processEvents();
                BOOST_FOREACH(EventSystem sysEv, eventEngine->getSystemEvents())
                {
                    switch(sysEv.getSystemType())
                    {
                        case EV_SYS_QUIT:
                            quit = true;
                            break;
                        case EV_SYS_RUNTHREAD:
                        {
                            ThreadFunction func = runThread;
                            DataCleanup clean = NULL;
                            threadPool.addJob(func, (void*)NULL, clean);
                        }
                            break;
                        case EV_SYS_UNKNOWN:
                            break;
                        default:
                            break;
                    }
                }

                /*End of Event Handling*/

                //Make all the game objects update themselves to any changes
                updateFrame();

                collisionEngine.performCollisionDetection(currentLevel->getLevelDimensions(), currentLevel->getmoveableObjects(), currentLevel->getimmoveableObjects(), eventEngine);

                SDL_Rect dim = currentLevel->getLevelDimensions();

                BOOST_FOREACH(CollisionEntity *entity, currentLevel->getmoveableObjects())
                {
                    checkBounds(entity, dim.w, dim.h);
                }
                BOOST_FOREACH(CollisionEntity *entity, currentLevel->getimmoveableObjects())
                {
                    checkBounds(entity, dim.w, dim.h);
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

        std::vector<Entity *> list = currentLevel->getLevelObjects();
        std::vector<UpdateThread> updateData(threadPool.getThreadCount());
        pthread_mutex_t countLock = PTHREAD_MUTEX_INITIALIZER;
        pthread_cond_t done = PTHREAD_COND_INITIALIZER;
        int count = threadPool.getThreadCount();

        pthread_mutex_lock(&countLock);

        for(int i = 0; i < threadPool.getThreadCount(); i++)
        {
            updateData[i].objectList = &list;
            updateData[i].dt = dt;
            updateData[i].count = &count;
            updateData[i].number = i;

            updateData[i].done = &done;
            updateData[i].countLock = &countLock;

            threadPool.addJob(updateFrameThread, (void *)&updateData[i], NULL);
        }

        pthread_cond_wait(&done, &countLock);
    }

    void *BallGame::updateFrameThread(void *data)
    {
        struct UpdateThread *updateData = (struct UpdateThread*)data;
        std::vector<Entity*> *list = updateData->objectList;

        //BOOST_FOREACH( Entity *object, currentLevel->getLevelObjects())
        for(int i = updateData->number; i < updateData->objectList->size(); i += (*updateData->count) + updateData->number)
        {
            Entity *object = (*list)[i];
            object->update(updateData->dt);
        }

        pthread_mutex_lock(updateData->countLock);
        (*updateData->count)--;
        if((*updateData->count) > 0)
        {
            pthread_mutex_unlock(updateData->countLock);
        }
        else
        {
            pthread_mutex_unlock(updateData->countLock);
            pthread_cond_signal(updateData->done);
        }
    }

void BallGame::checkBounds(CollisionEntity *entity, int screenWidth, int screenHeight)
{
    //STUB("Needs all the pointers removing");
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


