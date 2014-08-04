/*
Project:
Author: Brock
*/

#ifndef VISUALENTITY_H
#define VISUALENTITY_H

#include "Entity.h"
#include "RenderEngine.h"
#include <vector>

enum LAYER
{
    L_DEFAULT = 0,
    L_BACKGROUND1,
    L_BACKGROUND0,
    L_FOREGROUND
};

class VisualEntity: public Entity
{
    public:
        VisualEntity();

        VisualEntity( std::string filename, float x_i, float y_i, float width, float height, LAYER drawingLayer);

        VisualEntity(const VisualEntity& vEntity); //Copy constructor, needed so that reference counting in resource manager works...

        virtual ~VisualEntity();

        virtual void draw(RenderEngine renderEngine, vec2 offset);

        Rect& getPosDim();

        void setPos( float x, float y );

        void setPrevPos( float x, float y );

        float dotProduct( vec2 one, vec2 two );

        std::vector<float> projectOnto( vec2 axis );

        std::pair<float,float> minMaxProjectOnto(vec2 axis);

        std::vector<vec2> getVertices();

        std::vector<vec2> getAxes();

        std::vector<vec2> getPerpAxes();

        std::vector<vec2> getNormedAxes();

        int getSprite() {return sprite;}

    private:

    int sprite;
    Rect posDim;
    LAYER drawingLayer;
};

#endif // VISUALENTITY_H
