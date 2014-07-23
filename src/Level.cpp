#include "Level.h"
#include <boost/foreach.hpp>

//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level::Level()
    {
        int i;

        m_player = Player();
        drawableObjects.push_back(m_player);

        //tmpBlock = new Block( SDL_SWSURFACE, 200, 200, 32, 260, 260);

        for(i = 0; i < 6; i++)
        {
            Block tmpBlock( NULL, 20, 20, 32, 260 + i * 20, 460 - (20 * i));
            drawableObjects.push_back(tmpBlock);
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

    std::vector<Entity> Level::getLevelObjects()
    {
        return levelObjects;
    }

    int Level::getNumObjects()
    {
        return levelObjects.size();
    }

    std::string Level::getNextLevel()
    {
        return m_nextLevel;
    }

    void Level::draw(RenderEngine renderEngine)
    {
        renderEngine.clearScreen();//Not sure level should do this

        BOOST_FOREACH(VisualEntity object, drawableObjects)
        {
            object.draw(renderEngine);
        }

        renderEngine.show();
    }


    //------------------------------Mutators
