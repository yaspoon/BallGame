#include "Level.h"


//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level::Level()
    {
        int i;
        comp = 32;
        Block* tmpBlock;

        m_player = new Player();

        /*for( i=0; i < comp; i++ )
        {
            tmpBlock = new Block( SDL_SWSURFACE, 20, 20, 32, (float)260 + 20*i, (float)460-(20*i) );
            //tmpBlock = new Block( SDL_SWSURFACE, 20, 20, 32, (float)20*i, (float)460 );
            m_levelObjects[i] = (Entity*)tmpBlock;
        }*/

        tmpBlock = new Block( SDL_SWSURFACE, 200, 200, 32, 260, 460);

        /*for(i = 0; i < 6; i++)
        {
            tmpBlock = new Block( SDL_SWSURFACE, 20, 20, 32, 260 + i * 20, 460);
        }*/


        m_nextLevel = "none";
        m_numLevelObjects = 1;

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
        int i = 0;

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
