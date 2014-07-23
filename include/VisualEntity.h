/*
Project:
Author: Brock
*/

#ifndef VISUALENTITY_H
#define VISUALENTITY_H

#include "Entity.h"
#include "RenderEngine.h"
#include <SDL2/SDL_opengl.h>
#include <vector>

class VisualEntity: public Entity
{
    public:
        VisualEntity( std::string filename, float x_i, float y_i, float width, float height );

        VisualEntity(const VisualEntity& vEntity); //Copy constructor, needed so that reference counting in resource manager works...

        virtual ~VisualEntity();

        virtual void draw(RenderEngine renderEngine);

        virtual void collision( VisualEntity& collider ) {};

        Rect& getPosDim();

        void setPos( float x, float y );

        void setPrevPos( float x, float y );

        float dotProduct( vec2 one, vec2 two );

        std::vector<float> projectOnto( vec2 axis );

        std::vector<vec2> getVertices();

        std::vector<vec2> getAxes();

        std::vector<vec2> getPerpAxes();

        std::vector<vec2> getNormedAxes();

        COLLIDABLE getCtype();

        void setCtype( COLLIDABLE type );

    private:

    int sprite;
    Rect posDim;

    COLLIDABLE cType;

    Uint32 rmask;
    Uint32 gmask;
    Uint32 bmask;
    Uint32 amask;

    GLuint texture;
    GLenum texture_format;
    GLint nOfColors;

};

#endif // VISUALENTITY_H
