#include "Level.h"
#include <boost/foreach.hpp>

//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level::Level()
    {
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

    bool Level::initialise()
    {
        m_player = std::shared_ptr<Player>(new Player());

        //new Block(200, 40, 0, 460);
        //new Block(20, 20, 200, 420);

        /*for(int i = 0; i < 6; i++)
        {
            new Block(20, 20, 150 +(i * 20), 460);
            new Block(20, 20, 150 +(i * 20), 400);
        }*/

        new Block(640, 20, 0, 460);


        /*for(int i = 0; i < 6; i++)
        {
            new Block(20, 20, 260 + i * 20, 460 - (20 * i));
        }*/

        new Block(20, 20, 400, 360);

        STUB("Returning true by default for now");
        return true;
    }

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

    void Level::addEntity(Entity* entity)
    {
        levelObjects.push_back(entity);
    }

    void Level::removeEntity(Entity* entity)
    {
        for(std::vector<Entity*>::size_type i = 0; i < levelObjects.size(); i++)
        {
            if(levelObjects[i] == entity)
            {
                levelObjects.erase(levelObjects.begin() + i);
            }
        }
    }

    void Level::addDrawableObject(VisualEntity *drawable)
    {
        drawableObjects.push_back(drawable);
    }

    void Level::removeDrawableObject(VisualEntity *drawable)
    {
        for(std::vector<VisualEntity*>::size_type i = 0; i < drawableObjects.size(); i++)
        {
            if(drawableObjects[i] == drawable)
            {
                drawableObjects.erase(drawableObjects.begin() + i);
            }
        }
    }

    void Level::addCollidableObject(CollisionEntity *collider)
    {
        collidableObjects.push_back(collider);
    }

    void Level::removeCollidableObject(CollisionEntity *collider)
    {
        for(std::vector<CollisionEntity*>::size_type i = 0; i < collidableObjects.size(); i++)
        {
            if(collidableObjects[i] == collider)
            {
                collidableObjects.erase(collidableObjects.begin() + i);
            }
        }
    }
    //------------------------------Mutators
