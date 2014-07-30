#ifndef ENTITY_H
#define ENTITY_H

#include "bgCommon.h"
#include "EventSystem.h"
#include "EventInput.h"

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
        virtual void update( float dt ) =0;

        virtual void handleSystemEvent(EventSystem systemEvent) =0;

        virtual void handleInputEvent(EventInput inputEvent) =0;

};

#endif
