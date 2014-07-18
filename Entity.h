#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SDL2/SDL.h>
#include "bgCommon.h"
#include <list>

class Entity
{
    private:

    public:

//--------------------------------------Constructors/
        Entity();

//--------------------------------------Destructors/
        virtual ~Entity();

//--------------------------------------Methods/
    //------------------------------Accessors

    //------------------------------Mutators
        virtual void update( float dt ) {}

        virtual void draw( SDL_Window* const mainSurface ) {}

        virtual void handleEvents( SDL_Event& event ) {}

};

#endif
