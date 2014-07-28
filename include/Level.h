#ifndef LEVELDEF
#define LEVELDEF

#include "Block.h"
#include "Player.h"
#include "RenderEngine.h"
#include "CollisionEntity.h"

class Level
{

    private:
//--------------------------------------Data/
    const static int m_maxNumObjects = 64;
    std::vector<Entity*> levelObjects;
    std::vector<VisualEntity*> drawableObjects;
    std::vector<CollisionEntity*> collidableObjects;
    SDL_Rect m_startPosition;
    SDL_Rect m_endPosition;
    std::string m_nextLevel;
    std::shared_ptr<Player> m_player;

    public:
//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level();

    Level( std::string );

//--------------------------------------Destructors/
    ~Level();

//--------------------------------------Methods/
    bool initialise();
    //------------------------------Accessors
    SDL_Rect getStartPosition();

    SDL_Rect getEndPosition();

    std::vector<Entity*> getLevelObjects();

    std::vector<VisualEntity*> getDrawableObjects();

    std::vector<CollisionEntity*> getCollidableObjects();

    int getNumObjects();

    std::string getNextLevel();

    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    void addDrawableObject(VisualEntity *drawable);
    void removeDrawableObject(VisualEntity *drawable);

    void addCollidableObject(CollisionEntity *collider);
    void removeCollidableObject(CollisionEntity *collider);

    //------------------------------Mutators
    void draw(RenderEngine renderEngine);

};

#endif
