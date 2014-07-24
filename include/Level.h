#ifndef LEVELDEF
#define LEVELDEF

#include "Block.h"
#include "Player.h"
#include "RenderEngine.h"

class Level
{

    private:
//--------------------------------------Data/
    const static int m_maxNumObjects = 64;
    std::vector<Entity*> levelObjects;
    std::vector<VisualEntity*> drawableObjects;
    SDL_Rect m_startPosition;
    SDL_Rect m_endPosition;
    std::string m_nextLevel;
    Player m_player;

    public:
//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level();

    Level( std::string );

//--------------------------------------Destructors/
    ~Level();

//--------------------------------------Methods/
    //------------------------------Accessors
    SDL_Rect getStartPosition();

    SDL_Rect getEndPosition();

    std::vector<Entity*> getLevelObjects();

    std::vector<VisualEntity*> getDrawableObjects();

    int getNumObjects();

    std::string getNextLevel();

    //------------------------------Mutators
    void draw(RenderEngine renderEngine);

};

#endif
