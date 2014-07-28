#ifndef _BALLGAME_H__
#define _BALLGAME_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "Entity.h"
#include "Level.h"
#include "bgCommon.h"
#include "VisualEntity.h"
#include "RenderEngine.h"
#include "ResourceManager.h"
#include "EventEngine.h"

class BallGame
{

private:

//--------------------------------------Data
    RenderEngine renderEngine;
    std::shared_ptr<ResourceManager> resourceManager;
    std::shared_ptr<EventEngine> eventEngine;
    const static int FRAMES_PER_SECOND = 60;
    std::string m_gameName;

    SDL_Event events;

    int windowFlags;

    bool quit;

    int frame;
    Uint32 lastframe;

    /*Load default Level*/
    std::unique_ptr<Level> currentLevel;
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

    /*Collision_t getCollision(Rect box1, Rect box2);

    bool collide( VisualEntity collidee, VisualEntity collider, Collision_t *collision);*/

    void checkBounds(VisualEntity *entity);

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
    RenderEngine getRenderEngine();
    std::shared_ptr<ResourceManager> getResourceManager();
    std::shared_ptr<EventEngine> getEventEngine();

    //------------------------------Mutators
    void addEntity(Entity entity_i);

    void removeEntity(Entity entity_i);

    //------------------------------Imperita/
    int ballGameMain();

    //Collision_t checkMove( Rect& object, int yvel, int xvel );

    void updateFrame();

    void checkCollisions();


};
#endif
