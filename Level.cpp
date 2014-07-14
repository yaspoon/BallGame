#include "Level.h"


//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level::Level()
    {
        int i;
        comp = 32;
        Block* tmpBlock;

        m_player = new Player();
        m_numLevelObjects = 0;

        //tmpBlock = new Block( SDL_SWSURFACE, 200, 200, 32, 260, 260);

        for(i = 0; i < 6; i++)
        {
            tmpBlock = new Block( NULL, 20, 20, 32, 260 + i * 20, 460 - (20 * i));
            m_levelObjects[m_numLevelObjects] = dynamic_cast<Entity*>(tmpBlock);
            m_numLevelObjects += 1;
        }


        m_nextLevel = "none";

        m_startPosition.x = 140;
        m_startPosition.y = 180;

        m_endPosition.x = 240;
        m_endPosition.y = 240;
    }

    Level::Level( std::string )
    {

    }

//--------------------------------------Destructors/
    Level::~Level()
    {
        for(int i = 0; i < m_numLevelObjects; i++)
        {
            delete m_levelObjects[i];
        }

        delete m_player;
    }

//--------------------------------------Methods/
    //------------------------------Accessors
    SDL_Rect Level::getStartPosition()
    {
        return m_startPosition;
    }

    SDL_Rect Level::getEndPosition()
    {
        return m_endPosition;
    }

    Entity** Level::getLevelObjects()
    {
        return m_levelObjects;
    }

    int Level::getNumObjects()
    {
        return m_numLevelObjects;
    }

    std::string* Level::getNextLevel()
    {
        return &m_nextLevel;
    }


    //------------------------------Mutators
