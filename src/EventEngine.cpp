#include "EventEngine.h"
#include "SDL2/SDL.h"
#include "boost/foreach.hpp"

EventEngine::EventEngine()
{
    inputMap[KEY_LEFT] = SDL_SCANCODE_LEFT;
    inputMap[KEY_RIGHT] = SDL_SCANCODE_RIGHT;
    inputMap[KEY_JUMP] = SDL_SCANCODE_SPACE;
    systemMap[EV_SYS_QUIT] = SDL_SCANCODE_Q;
}

EventEngine::~EventEngine()
{
    //dtor
}

void EventEngine::generateEvents()
{
    SDL_Event event;
    while( SDL_PollEvent(&event))
    {
        switch( event.type )
        {
            case SDL_QUIT:
            {
                systemEvents.push_back(EventSystem(EV_SYS_QUIT));
            }
                break;
            case SDL_KEYDOWN:
                {
                    if(event.key.repeat == 0)
                    {
                        if(systemMap[EV_SYS_QUIT] == event.key.keysym.scancode)
                        {
                            systemEvents.push_back(EventSystem(EV_SYS_QUIT));
                            break;
                        }

                        if(inputMap[KEY_LEFT] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_LEFT));
                            break;
                        }

                        if(inputMap[KEY_RIGHT] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_RIGHT));
                            break;
                        }

                        if(inputMap[KEY_JUMP] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_JUMP));
                            break;
                        }
                        /*switch(event.key.keysym.scancode)
                        {
                            case SDL_SCANCODE_Q:
                                systemEvents.push_back(EventSystem(EV_SYS_QUIT));
                            break;
                            case SDL_SCANCODE_LEFT:
                                inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_LEFT));
                            break;
                            case SDL_SCANCODE_RIGHT:
                                inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_RIGHT));
                            break;
                        }*/
                    }
                }
                break;
            case SDL_KEYUP:
                {
                    if(event.key.repeat == 0)
                    {
                        if(inputMap[KEY_LEFT] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYUP, KEY_LEFT));
                            break;
                        }

                        if(inputMap[KEY_RIGHT] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYUP, KEY_RIGHT));
                            break;
                        }
                        /*switch(event.key.keysym.scancode)
                        {
                            case SDL_SCANCODE_LEFT:
                                inputEvents.push_back(EventInput(EV_INPUT_KEYUP, KEY_LEFT));
                            break;
                            case SDL_SCANCODE_RIGHT:
                                inputEvents.push_back(EventInput(EV_INPUT_KEYUP, KEY_RIGHT));
                            break;
                        }*/
                    }
                }
                break;
            default:
                break;
        }//End switch( events.type )
    }//End event polling loop
}


void EventEngine::processEvents()
{
    generateEvents();

    BOOST_FOREACH(EventSystem sysEv, systemEvents)
    {
        BOOST_FOREACH(Entity *entity, systemEventEntities)
        {
            entity->handleSystemEvent(sysEv);
        }
    }

    BOOST_FOREACH(EventInput inputEv, inputEvents)
    {
        BOOST_FOREACH(Entity *entity, inputEventEntities)
        {
            entity->handleInputEvent(inputEv);
        }
    }

    BOOST_FOREACH(EventCollision collEv, collisionEvents)
    {
        BOOST_FOREACH(CollisionEntity *entity, collisionEventEntities)
        {
            entity->handleCollisionEvent(collEv.getCollider());
        }
    }

    inputEvents.clear();
    collisionEvents.clear();

}

std::vector<EventSystem> EventEngine::getSystemEvents()
{
    return systemEvents;
}

bool EventEngine::registerForEvents(Entity *entityToReg, EventType typeToReg)
{
    bool retval = true;
    switch(typeToReg)
    {
        case EV_SYSTEM:
            systemEventEntities.push_back(entityToReg);
        break;
        case EV_INPUT:
            inputEventEntities.push_back(entityToReg);
        break;
        case EV_COLLISION:
            collisionEventEntities.push_back((CollisionEntity*)entityToReg);
        break;
        default:
        break;
    }

    return retval;
}

 bool EventEngine::deregisterForEvents(Entity *entityToDeReg, EventType typeToDeReg)
 {
     bool retval = true;
     switch(typeToDeReg)
     {
        case EV_SYSTEM:
        break;
        case EV_INPUT:
        {
            for(std::vector<EventInput>::size_type i = 0; i < inputEventEntities.size(); i++)
            {
                if(inputEventEntities[i] == entityToDeReg)
                {
                    inputEventEntities.erase(inputEventEntities.begin() + i);
                }
            }
        }
        break;
        case EV_COLLISION:
        break;
        case EV_UNKNOWN:
            break;
        default:
            break;
     }

     return retval;
 }

void EventEngine::addCollisionEvent(EventCollision collision)
{
    collisionEvents.push_back(collision);
}
