#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <SDL/SDL.h>
#include "bgCommon.h"
#include <list>

class Entity
{
    private:

    public:

//--------------------------------------Constructors/
        Entity();

        Entity( float , float );

//--------------------------------------Destructors/
        virtual ~Entity();

//--------------------------------------Methods/
    //------------------------------Accessors

    //------------------------------Mutators
        virtual void update( float dt ) {}

        virtual void draw( SDL_Surface* const mainSurface ) {}

        virtual void handleEvents( SDL_Event& event ) {}

};

#endif
