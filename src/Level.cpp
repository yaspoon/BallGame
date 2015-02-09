#include "Level.h"
#include <boost/foreach.hpp>
#include "BallGame.h"
#include "MoveableBlock.h"

//--------------------------------------Constructors/
    //Default Constructor loads the default level
    Level::Level()
    {
        m_nextLevel = "none";

        levelDimensions.x = 0;
        levelDimensions.y = 0;
        levelDimensions.w = 1280;
        levelDimensions.h = 480;
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
        backgroundColour = {74, 182, 217, 0};
        BALLGAME.getRenderEngine().setBackgroundColour(backgroundColour);

        CollisionShape blockShape;
        blockShape.points.push_back((vec2){0, 0});
        blockShape.points.push_back((vec2){20, 0});
        blockShape.points.push_back((vec2){20, 20});
        blockShape.points.push_back((vec2){0, 20});

        new Block("images/Proj/edge_left.png", 20, 20, 0, 460, L_DEFAULT, blockShape);
        for(int i = 1; i < ((levelDimensions.w / 20) - 1); i++)
        {
            new Block("images/Proj/grass_top.png", 20, 20, i * 20, 460, L_DEFAULT, blockShape);
        }
        new Block("images/Proj/edge_right.png", 20, 20, levelDimensions.w - 20, 460, L_DEFAULT, blockShape);
        new Block(20, 20, 960, 400, L_DEFAULT, blockShape);


        for(int i = 0; i < 1000; i++)
        {
            new Block(20, 20, 260 + i * 20, 440 - (20 * i), L_DEFAULT, blockShape);
        }

        /*for(int i = 0; i < (levelDimensions.w / 48); i++)
        {
            new Block("images/tree-1.png", 48, 76, i * (48 * 2), 432, L_BACKGROUND0);
            new Block("images/tree-2.png", 48, 76, 48 + i * (48 * 2), 384, L_BACKGROUND1);
        }*/

        //new Block("images/sun.png", 200, 200, 320, 0, L_BACKGROUND1);

        CollisionShape triangleShape;
        triangleShape.points.push_back((vec2){0, 100});
        triangleShape.points.push_back((vec2){200, 0});
        triangleShape.points.push_back((vec2){200, 100});
        new MoveableBlock("images/triangle.png", 200, 100, 0, 360, L_DEFAULT, triangleShape, (vec2){1,0}, 20);

        STUB("Returning true by default for now");
        return true;
    }

    //------------------------------Accessors
    SDL_Rect Level::getLevelDimensions()
    {
        return levelDimensions;
    }

    std::vector<Entity*> Level::getLevelObjects()
    {
        return levelObjects;
    }

    std::vector<VisualEntity*> Level::getDrawableObjects()
    {
        return drawableObjects;
    }

    std::vector<CollisionEntity*> Level::getmoveableObjects()
    {
        return moveableObjects;
    }

    std::vector<CollisionEntity*> Level::getimmoveableObjects()
    {
        return immoveableObjects;
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
        vec2 offset;
        Rect posDim = m_player->getPosDim();
        ScreenDimensions screenDims = renderEngine.getScreenDimensions();


        if((posDim.x + (posDim.w / 2)) <= (screenDims.width / 2))
        {
            offset.x = 0;
            offset.y = 0;
        }
        else if((posDim.x + (posDim.w / 2)) >= (levelDimensions.w - (screenDims.width / 2)))
        {
            offset.x = (screenDims.width / 2) - (levelDimensions.w - (screenDims.width / 2));
            offset.y = 0;
        }
        else
        {
            offset.x = (screenDims.width / 2) - (posDim.x + (posDim.w / 2));
            offset.y = 0;
        }

        //Draw objects that are furtherest in the background first
        BOOST_FOREACH(VisualEntity* backgroundObject, backgroundObjects1)
        {
            backgroundObject->draw(renderEngine, offset);
        }

        //Draw closest background objects next
        BOOST_FOREACH(VisualEntity* backgroundObject, backgroundObjects0)
        {
            backgroundObject->draw(renderEngine, offset);
        }

        //Draw objects in main layer
        BOOST_FOREACH(VisualEntity* object, drawableObjects)
        {
            object->draw(renderEngine, offset);
        }

        BOOST_FOREACH(VisualEntity* foregroundObject, foregroundObjects)
        {
            foregroundObject->draw(renderEngine, offset);
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

    void Level::addDrawableObject(VisualEntity *drawable, LAYER drawingLayer)
    {
        switch(drawingLayer)
        {
            case L_DEFAULT:
                drawableObjects.push_back(drawable);
                break;
            case L_BACKGROUND1:
                backgroundObjects1.push_back(drawable);
                break;
            case L_BACKGROUND0:
                backgroundObjects0.push_back(drawable);
                break;
            case L_FOREGROUND:
                foregroundObjects.push_back(drawable);
                break;

        }
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
        COLLIDABLE type = collider->getCtype();
        switch(type)
        {
            case C_MOVEABLE:
                moveableObjects.push_back(collider);
                break;
            case C_IMMOVABLE:
                immoveableObjects.push_back(collider);
                break;
        }
    }

    void Level::removeCollidableObject(CollisionEntity *collider)
    {
        std::vector<CollisionEntity*> tmp = immoveableObjects;
        tmp.insert(tmp.end(), moveableObjects.begin(), moveableObjects.end());
        for(std::vector<CollisionEntity*>::size_type i = 0; i < tmp.size(); i++)
        {
            switch(collider->getCtype())
            {
                case C_MOVEABLE:
                    if(moveableObjects[i] == collider)
                    {
                        moveableObjects.erase(moveableObjects.begin() + i);
                    }
                    break;
                case C_IMMOVABLE:
                    if(immoveableObjects[i] == collider)
                    {
                        immoveableObjects.erase(immoveableObjects.begin() + i);
                    }
                    break;
            }

        }
    }
    //------------------------------Mutators
