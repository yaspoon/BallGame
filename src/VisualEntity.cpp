/*
Project:
Author: Brock
*/

#include "VisualEntity.h"
#include "BallGame.h"
#include <string>
#include <vector>

VisualEntity::VisualEntity()
:Entity()
{
    this->drawingLayer = L_DEFAULT;
    posDim.w = 100;
    posDim.h = 40;
    posDim.x = 0;
    posDim.y = 0;

    sprite = BALLGAME.getResourceManager()->loadTexture("images/null.png");
    BALLGAME.getCurrentLevel()->addDrawableObject(this, L_DEFAULT);
}

VisualEntity::VisualEntity( std::string filename, float x_i, float y_i, float width, float height, LAYER drawingLayer)
:Entity( )
{
    this->drawingLayer = drawingLayer;
    posDim.w = width;
    posDim.h = height;
    posDim.x = x_i;
    posDim.y = y_i;

    sprite = BALLGAME.getResourceManager()->loadTexture(filename);
    BALLGAME.getCurrentLevel()->addDrawableObject(this, drawingLayer);
}

/*
*Copy constructor
*This is pretty feral....
*The copy constructor needs to "load" the texture again
*So that the reference count gets increased. So that when
* the other object gets destructed the image won't get cleaned up
* because we've loaded it here..
*/
VisualEntity::VisualEntity(const VisualEntity& vEntity)
{
    *this = vEntity;
    BALLGAME.getResourceManager()->loadTexture(vEntity.sprite);
    BALLGAME.getCurrentLevel()->addDrawableObject(this, vEntity.drawingLayer);
}

VisualEntity::~VisualEntity()
{
    //STUB("No cleanup for sprite yet because no resource cleanup functions yet...");
    BALLGAME.getResourceManager()->unloadResource(sprite);
    BALLGAME.getCurrentLevel()->removeDrawableObject(this);
}

void VisualEntity::draw(RenderEngine renderEngine, vec2 offset)
{
    SDL_Rect dest;

    switch(drawingLayer)
    {
        case L_DEFAULT: //Do nothing we want default scrolling speed
            break;
        case L_BACKGROUND1: //Furtherest away so slowest scrolling speed
            offset.x = offset.x * 0.5;
            offset.y = offset.y * 0.5;
            break;
        case L_BACKGROUND0:
            offset.x = offset.x * 0.8;
            offset.y = offset.y * 0.8;
            break;
        case L_FOREGROUND:
            break;
    }

    dest.x = (int)(posDim.x + offset.x);
    dest.y = (int)(posDim.y + offset.y);
    dest.w = (int)posDim.w;
    dest.h = (int)posDim.h;

    renderEngine.draw(sprite, NULL, &dest);
}

Rect& VisualEntity::getPosDim()
{
    return posDim;
}

void VisualEntity::setPos( float x, float y )
{
    posDim.x = x;
    posDim.y = y;
}
