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
    posDim.w = 100;
    posDim.h = 40;
    posDim.x = 0;
    posDim.y = 0;
    posDim.prevX = 0;
    posDim.prevY = 0;

    sprite = BALLGAME.getResourceManager()->loadTexture("images/null.png");
    BALLGAME.getCurrentLevel()->addDrawableObject(this);
}

VisualEntity::VisualEntity( std::string filename, float x_i, float y_i, float width, float height )
:Entity( )
{
    posDim.w = width;
    posDim.h = height;
    posDim.x = x_i;
    posDim.y = y_i;
    posDim.prevX = x_i;
    posDim.prevY = y_i;

    sprite = BALLGAME.getResourceManager()->loadTexture(filename);
    BALLGAME.getCurrentLevel()->addDrawableObject(this);
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
    BALLGAME.getCurrentLevel()->addDrawableObject(this);
}

VisualEntity::~VisualEntity()
{
    //STUB("No cleanup for sprite yet because no resource cleanup functions yet...");
    BALLGAME.getResourceManager()->unloadResource(sprite);
    BALLGAME.getCurrentLevel()->removeDrawableObject(this);
}

void VisualEntity::draw(RenderEngine renderEngine)
{
    SDL_Rect dest;
    dest.x = (int)posDim.x;
    dest.y = (int)posDim.y;
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
        float dp = dotProduct(vertex, axis);//vertex.x * axis.x) + (vertex.y * axis.y); //Calc dot product of vertex and axis to project it onto the axis
        projections.push_back(dp);
    }

    return projections;
}

std::pair<float,float> VisualEntity::minMaxProjectOnto(vec2 axis)
{
    std::vector<float> projectedPoints = projectOnto(axis);
    float min = projectedPoints[0];
    float max = projectedPoints[0];
    for(std::vector<float>::iterator it = projectedPoints.begin(); it != projectedPoints.end(); ++it)
    {
        if(*it < min)
        {
            min = *it;
        }
        if(*it > max)
        {
            max = *it;
        }
    }
    std::pair<float,float> retval;
    retval.first = min;
    retval.second = max;
    return retval;
}

float VisualEntity::dotProduct( vec2 one, vec2 two )
{
    return (one.x * two.x) + (one.y * two.y );
}
