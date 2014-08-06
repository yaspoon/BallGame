#include "BallGame.h"
#include "CollisionEntity.h"

CollisionEntity::CollisionEntity()
:VisualEntity()
{
        //BALLGAME.getCurrentLevel()->addCollidableObject(this);
        xvel = 0;
        yvel = 0;
        onGround = false;
        shapeType = CS_UNKNOWN;
}

CollisionEntity::CollisionEntity(std::string filename, float x, float y, float width, float height, LAYER drawingLayer)
:VisualEntity(filename, x, y, width, height, drawingLayer)
{
    xvel = 0;
    yvel = 0;
    onGround = false;
    this->shapeType = CS_UNKNOWN;
}

CollisionEntity::CollisionEntity(std::string filename, float x, float y, float width, float height, LAYER drawingLayer, ColliderShapeType shapeType)
:VisualEntity(filename, x, y, width, height, drawingLayer)
{
    if(drawingLayer == L_DEFAULT)
    {
        BALLGAME.getCurrentLevel()->addCollidableObject(this);
    }
    xvel = 0;
    yvel = 0;
    onGround = false;
    this->shapeType = shapeType;
}

CollisionEntity::CollisionEntity(std::string filename, float x, float y, float width, float height, LAYER drawingLayer, ColliderShapeType shapeType, CollisionShape shape)
:VisualEntity(filename, x, y, width, height, drawingLayer)
{
    if(drawingLayer == L_DEFAULT)
    {
        BALLGAME.getCurrentLevel()->addCollidableObject(this);
    }
    xvel = 0;
    yvel = 0;
    onGround = false;
    this->shapeType = shapeType;
    this->shape = shape;
}

CollisionEntity::~CollisionEntity()
{
    BALLGAME.getCurrentLevel()->removeCollidableObject(this);
}

float CollisionEntity::getXvel()
{
    return xvel;
}

float CollisionEntity::getYvel()
{
    return yvel;
}

bool CollisionEntity::getOnGround()
{
    return onGround;
}

COLLIDABLE CollisionEntity::getCtype()
{
    return cType;
}

void CollisionEntity::setXvel(float newVel)
{
    xvel = newVel;
}

void CollisionEntity::setYvel(float newVel)
{
    yvel = newVel;
}

void CollisionEntity::setOnGround(bool isOnGround)
{
    onGround = isOnGround;
}

void CollisionEntity::setCtype( COLLIDABLE type )
{
    cType = type;
}

void CollisionEntity::setCollisionShape(CollisionShape newShape)
{
    shape = newShape;
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
std::vector<vec2> CollisionEntity::getVertices()
{
    std::vector<vec2> vertices;
    Rect posDim = getPosDim();

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

std::vector<vec2> CollisionEntity::getAxes()
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

std::vector<vec2> CollisionEntity::getPerpAxes()
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

std::vector<vec2> CollisionEntity::getNormedAxes()
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

std::vector<float> CollisionEntity::projectOnto( vec2 axis )
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

std::pair<float,float> CollisionEntity::minMaxProjectOnto(vec2 axis)
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

float CollisionEntity::dotProduct( vec2 one, vec2 two )
{
    return (one.x * two.x) + (one.y * two.y );
}
