#include "Entity.h"
#include "BallGame.h"


//--------------------------------------Constructors/
        Entity::Entity()
        {
            BALLGAME.getCurrentLevel()->addEntity(this);
        }

//--------------------------------------Destructors/
        Entity::~Entity()
        {
            BALLGAME.getCurrentLevel()->removeEntity(this);
        }

//--------------------------------------Methods/
    //------------------------------Accessors

    //------------------------------Mutators



