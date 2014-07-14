/*
Project:
Author: Brock
*/

#include "VisualEntity.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

VisualEntity::VisualEntity( std::string filename, float x_i, float y_i, float width, float height )
:Entity( )
{
    posDim.w = width;
    posDim.h = height;
    posDim.x = x_i;
    posDim.y = y_i;
    posDim.prevX = x_i;
    posDim.prevY = y_i;

    SDL_Surface* temp = IMG_Load( filename.c_str() );
    sprite = NULL;

    if( temp != NULL )
    {
        cout<<"Loaded "<<filename<<"\n";

        sprite = temp;//SDL_DisplayFormatAlpha( temp );

        if( sprite == NULL )
        {
            printf( "%s could not be loaded", filename.c_str() );
        }

//        SDL_SetAlpha( sprite, 0, 0 );

        //SDL_FreeSurface( temp );

        if( ( sprite->w & ( sprite->w - 1 ) ) !=0 )
        {
            printf( "Warning: sprite width is not a power of 2\n");
        }

        if( ( sprite->h & ( sprite->h - 1 ) ) !=0 )
        {
            printf( "Warning: sprite height is not a power of 2\n");
        }

        nOfColors = sprite->format->BytesPerPixel;
        if( nOfColors == 4 )
        {
            if( sprite->format->Rmask == 0x000000ff)
                texture_format=GL_RGBA;
            else
                texture_format=GL_BGRA;
        }
        else if( nOfColors == 3 )
        {
            if( sprite->format->Rmask == 0x000000ff)
                texture_format=GL_RGB;
            else
                texture_format=GL_BGR;
        }
        else
        {
            printf( "Warning: the image is not true color this will break\n");
        }

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        glEnable(GL_BLEND );

        glGenTextures( 1, &texture );

        glBindTexture( GL_TEXTURE_2D, texture );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, sprite->w, sprite->h, 0, texture_format, GL_UNSIGNED_BYTE, sprite->pixels );

    }
    else
    {
        cout<<"Couldn't load "<<filename<<"\n";
    }

    if( sprite )
    {
        SDL_FreeSurface( sprite );
    }
}

VisualEntity::~VisualEntity()
{
    glDeleteTextures( 1, &texture );
}

void VisualEntity::draw( SDL_Window* const mainSurface )
{
    SDL_Rect dest;
    dest.x = (int)posDim.x;
    dest.y = (int)posDim.y;
    dest.w = (int)posDim.w;
    dest.h = (int)posDim.h;

    //SDL_BlitSurface( sprite, NULL, mainSurface, &dest);

    glBindTexture( GL_TEXTURE_2D, texture );

    glBegin( GL_QUADS );
        glTexCoord2i( 0, 0 );
        glVertex3f( dest.x, dest.y + dest.h, 0.0f);

        glTexCoord2i( 1, 0 );
        glVertex3f( dest.x + dest.w, dest.y + dest.h, 0.0f );

        glTexCoord2i( 1, 1 );
        glVertex3f( dest.x + dest.w, dest.y, 0.0f );

        glTexCoord2i( 0, 1 );
        glVertex3f( dest.x, dest.y, 0.0f);
    glEnd();

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

void VisualEntity::setPrevPos( float x, float y )
{
    posDim.prevX = x;
    posDim.prevY = y;
}

/*
Creates the vertices of the box in the order
top left
topright
bottom right
bottom left

since in sdl (0,0) is the top left of the window
so why not start in the top left then
*/
std::vector<vec2> VisualEntity::getVertices()
{
    std::vector<vec2> vertices;

    vec2 topLeft;
    topLeft.x = posDim.x;
    topLeft.y = posDim.y;
    vertices.push_back(topLeft);

    vec2 topRight;
    topRight.x = posDim.x + posDim.w;
    topRight.y = posDim.y;
    vertices.push_back(topRight);

    vec2 bottomRight;
    bottomRight.x = posDim.x + posDim.w;
    bottomRight.y = posDim.y + posDim.h;
    vertices.push_back(bottomRight);

    vec2 bottomLeft;
    bottomLeft.x = posDim.x;
    bottomLeft.y = posDim.y + posDim.h;
    vertices.push_back(bottomLeft);

    return vertices;
}

std::vector<vec2> VisualEntity::getAxes()
{
    std::vector<vec2> vertices = getVertices();
    std::vector<vec2> axes;

    for(std::vector<vec2>::iterator it = vertices.begin(); it != vertices.end(); ++it)
    {
        vec2 first = *it;
        vec2 second;

        std::vector<vec2>::iterator itDup = it;

        if(++itDup == vertices.end())
        {
            second = *(vertices.begin());
        }
        else
        {
            second = *itDup;
        }

        vec2 axis;
        axis.x = second.x - first.x;
        axis.y = second.y - first.y;

        axes.push_back(axis);

    }

    return axes;
}

std::vector<vec2> VisualEntity::getPerpAxes()
{
    std::vector<vec2> axes = getAxes();

    for(std::vector<vec2>::iterator it = axes.begin(); it != axes.end(); ++it)
    {
        vec2 axis = *it;

        float tmp = axis.x;
        axis.x = -(axis.y);
        axis.y = tmp;

        *it = axis;
    }

    return axes;
}

std::vector<vec2> VisualEntity::getNormedAxes()
{
    /*std::vector<vec2> axes = getPerpAxes();

    for(std::vector<vec2>::iterator it = axes.begin(); it != axes.end(); ++it)
    {
        vec2 axis = *it;

        float length = sqrt((axis.x * axis.x) + (axis.y * axis.y));

        axis.x = axis.x / length;
        axis.y = axis.y / length;

        *it = axis;
    }*/
    std::vector<vec2> axes;
    vec2 xaxis = {1, 0};
    vec2 yaxis = {0, 1};
    axes.push_back(xaxis);
    axes.push_back(yaxis);

    return axes;
}

std::vector<float> VisualEntity::projectOnto( vec2 axis )
{
    std::vector<float> projections;
    std::vector<vec2> vertices = getVertices();

    for(std::vector<vec2>::iterator it = vertices.begin(); it != vertices.end(); ++it) //project each vertex onto the given axis
    {
        vec2 vertex = *it;
        float dp = (vertex.x * axis.x) + (vertex.y * axis.y); //Calc dot product of vertex and axis to project it onto the axis
        projections.push_back(dp);
    }

    return projections;
}

float VisualEntity::dotProduct( vec2 one, vec2 two )
{
    return (one.x * two.x) + (one.y * two.y );
}

COLLIDABLE VisualEntity::getCtype()
{
    return cType;
}

void VisualEntity::setCtype( COLLIDABLE type )
{
    cType = type;
}
