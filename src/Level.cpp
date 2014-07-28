#include "Level.h"
#include <boost/foreach.hpp>

//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level::Level()
    {
        int i;

        m_player = Player();
        levelObjects.push_back(&m_player);
        drawableObjects.push_back(&m_player);

        //tmpBlock = new Block( SDL_SWSURFACE, 200, 200, 32, 260, 260);

        for(i = 0; i < 6; i++)
        {
            //Block *tmpBlock= new Block( NULL, 20, 20, 32, 260 + i * 20, 460 - (20 * i));
            //levelObjects.push_back(tmpBlock);
            //drawableObjects.push_back(tmpBlock);
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

    std::vector<Entity*> Level::getLevelObjects()
    {
        return levelObjects;
    }

    std::vector<VisualEntity*> Level::getDrawableObjects()
    {
        return drawableObjects;
    }

    std::vector<CollisionEntity*> Level::getCollidableObjects()
    {
        return collidableObjects;
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

        BOOST_FOREACH(VisualEntity* object, drawableObjects)
        {
            object->draw(renderEngine);
        }

        renderEngine.show();
    }

    void Level::addCollidableObject(CollisionEntity *collider)
    {
        collidableObjects.push_back(collider);
    }

    void Level::removeCollidableObject(CollisionEntity *collider)
    {
        for(int i = 0; i < collidableObjects.size(); i++)
        {
            if(collidableObjects[i] == collider)
            {
                collidableObjects.erase(collidableObjects.begin() + i);
            }
        }
    }
    //------------------------------Mutators
