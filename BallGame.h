#ifndef _BALLGAME_H__
#define _BALLGAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Entity.h"
#include "CollisionHandle.h"
#include "bgCommon.h"
#include "VisualEntity.h"

class BallGame
{

private:

//--------------------------------------Data
    SDL_Window *mainWindow;

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


    std::vector<Entity> entities;
    std::vector<Entity> addedEntities;
    std::vector<Entity> removedEntities;

    //Return value when ballgame quits
    int retVal;

//--------------------------------------Private methods/

    BallGame();

    bool initSDL();

    void handleKeyPress( SDL_Event );

    void proccessAddedObjects();

    void proccessRemovedObjects();

    Collision_t getCollision(Rect box1, Rect box2);

    bool collide( VisualEntity collidee, VisualEntity collider, Collision_t *collision);

    void checkBounds( VisualEntity entity );



public:

    SDL_Renderer *renderer; //Yes this is terrible that it's public but ballgame has enough useless methods as it is...
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
    void addEntity(Entity entity_i);

    void removeEntity(Entity entity_i);

    //------------------------------Imperita/
    int ballGameMain();

    Collision_t checkMove( Rect& object, int yvel, int xvel );

    void updateFrame();

    void drawFrame();

    void checkCollisions();

};
#endif
