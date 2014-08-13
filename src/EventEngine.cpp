#include "EventEngine.h"
#include "SDL2/SDL.h"
#include "boost/foreach.hpp"

EventEngine::EventEngine()
{
    inputMap[KEY_LEFT] = SDL_SCANCODE_LEFT;
    inputMap[KEY_RIGHT] = SDL_SCANCODE_RIGHT;
    inputMap[KEY_JUMP] = SDL_SCANCODE_SPACE;
    inputMap[KEY_Q] = SDL_SCANCODE_Q;
    inputMap[KEY_F1] = SDL_SCANCODE_F1;
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
                        if(inputMap[KEY_Q] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_Q));
                            break;
                        }

                        if(inputMap[KEY_F1] == event.key.keysym.scancode)
                        {
                            inputEvents.push_back(EventInput(EV_INPUT_KEYDOWN, KEY_F1));
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
        collEv.sendToObject();
    }
}

std::vector<EventSystem> EventEngine::getSystemEvents()
{
    return systemEvents;
}

std::vector<EventInput> EventEngine::getInputEvents()
{
    return inputEvents;
}

std::vector<EventCollision> EventEngine::getCollisionEvents()
{
    return collisionEvents;
}

void EventEngine::clearEventQueues()
{
    inputEvents.clear();
    collisionEvents.clear();
    systemEvents.clear();
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
