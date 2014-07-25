#include "EventEngine.h"
#include "SDL2/SDL.h"

EventEngine::EventEngine()
{
    //ctor
}

EventEngine::~EventEngine()
{
    //dtor
}

void EventEngine::processEvents()
{
    SDL_Event event;
    while( SDL_PollEvent(&event))
    {
        switch( event.type )
        {
            case SDL_QUIT:
            {
                EventSystem sysEv(EV_SYS_QUIT);
                Event tmp(sysEv);
                events.push_back(tmp);
            }
                break;
            case SDL_KEYDOWN:

                break;
            case SDL_KEYUP:

                break;
            default:
                break;
        }//End switch( events.type )
    }//End event polling loop
}
