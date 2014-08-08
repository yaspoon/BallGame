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
    std::vector<VisualEntity*> backgroundObjects0;
    std::vector<VisualEntity*> backgroundObjects1;
    std::vector<VisualEntity*> foregroundObjects;
    std::vector<CollisionEntity*> moveableObjects;
    std::vector<CollisionEntity*> immoveableObjects;
    SDL_Rect levelDimensions;
    std::string m_nextLevel;
    std::shared_ptr<Player> m_player;
    SDL_Color backgroundColour;

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
    SDL_Rect getLevelDimensions();

    std::vector<Entity*> getLevelObjects();

    std::vector<VisualEntity*> getDrawableObjects();

    std::vector<CollisionEntity*> getmoveableObjects();
    std::vector<CollisionEntity*> getimmoveableObjects();

    int getNumObjects();

    std::string getNextLevel();

    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    void addDrawableObject(VisualEntity *drawable, LAYER drawingLayer);
    void removeDrawableObject(VisualEntity *drawable);

    void addCollidableObject(CollisionEntity *collider);
    void removeCollidableObject(CollisionEntity *collider);

    //------------------------------Mutators
    void draw(RenderEngine renderEngine);

};

#endif
