#ifndef _BALLGAME_H__
#define _BALLGAME_H__

#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include "Entity.h"
#include "CollisionHandle.h"
#include "bgCommon.h"
#include "VisualEntity.h"

typedef std::list<Entity*> EntityList;

class BallGame
{

private:

//--------------------------------------Data
    SDL_Surface* mainWindow;

    int screenWidth;
    int screenHeight;
    int screenBpp;
    SDL_Rect screenDim;

    const static int FRAMES_PER_SECOND = 60;
    std::string m_gameName;

    SDL_Event events;

    int windowFlags;

    bool quit;

    int frame;
    Uint32 lastframe;


    EntityList entities;
    EntityList addedEntities;
    EntityList removedEntities;

    //Return value when ballgame quits
    int retVal;

//--------------------------------------Private methods/

    BallGame();

    bool initSDL();

    void setupOpengl( int screenWidth_i, int screenHeight_i );

    void handleKeyPress( SDL_Event );

    void applySurface( const float& x, const float& y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* );

    void proccessAddedObjects();

    void proccessRemovedObjects();

    Collision_t getCollision(Rect box1, Rect box2);

    bool collide( VisualEntity* collidee, VisualEntity* collider, Collision_t *collision);

    void checkBounds( VisualEntity* entity );



public:

//--------------------------------------Constructors/
    static BallGame& instance()
    {
        static BallGame instance;
        return instance;
    }

//--------------------------------------Destructors/
    ~BallGame();

//--------------------------------------Methods/
    //------------------------------Accessors
    SDL_Rect& getScreenDim();

    //------------------------------Mutators
    void addEntity( Entity* entity_i);

    void removeEntity( Entity* entity_i );

    //------------------------------Imperita/
    int ballGameMain();

    Collision_t checkMove( Rect& object, int yvel, int xvel );

    void updateFrame();

    void drawFrame();

    void checkCollisions();

};
#endif
