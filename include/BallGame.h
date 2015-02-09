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
#include "CollisionEngine.h"
#include "ThreadPool.h"

struct UpdateThread
{
    int number;
    int *count;
    pthread_mutex_t *countLock;
    float dt;
    std::vector<Entity *> *objectList;
    pthread_cond_t *done;
};

class BallGame
{

private:

//--------------------------------------Data
    RenderEngine renderEngine;
    std::shared_ptr<ResourceManager> resourceManager;
    std::shared_ptr<EventEngine> eventEngine;
    const static int FRAMES_PER_SECOND = 60;
    std::string m_gameName;
    ThreadPool threadPool;

    bool quit;

    int frame;
    Uint32 lastframe;

    /*Load default Level*/
    Level *currentLevel;
    std::vector<Entity> addedEntities;
    std::vector<Entity> removedEntities;

    //Return value when ballgame quits
    int retVal;

//--------------------------------------Private methods/

    BallGame();

    void checkBounds(CollisionEntity *entity, int screenWidth, int screenHeight);

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
    Level *getCurrentLevel();
    CollisionEngine collisionEngine;

    //------------------------------Mutators

    //------------------------------Imperita/
    int ballGameMain();

    void updateFrame();
    static void *updateFrameThread(void *data);
};
#endif
