#ifndef COLLISIONENTITY_H
#define COLLISIONENTITY_H

#include "VisualEntity.h"
#include "bgCommon.h"

enum ColliderShapeType
{
    CS_UNKNOWN = 0,
    CS_AABB,
    CS_CIRCLE
};

typedef struct
{
    std::vector<vec2> points;
    float radius; //Only applies to circles
} CollisionShape;

class CollisionEntity: public VisualEntity
{
    public:
        CollisionEntity();
        CollisionEntity(std::string filename, float x, float y, float width, float height, LAYER drawingLayer);
        CollisionEntity(std::string filename, float x, float y, float width, float height, LAYER drawingLayer, ColliderShapeType shapeType);
        CollisionEntity(std::string filename, float x, float y, float width, float height, LAYER drawingLayer, ColliderShapeType shapeType, CollisionShape shape);
        virtual ~CollisionEntity();

        float getXvel();
        float getYvel();
        bool getOnGround();
        COLLIDABLE getCtype();

        void setXvel(float newVel);
        void setYvel(float newVel);
        void setOnGround(bool isOnGround);
        void setCtype(COLLIDABLE type);
        void setCollisionShape(CollisionShape newShape);
        virtual void handleCollisionEvent(CollisionEntity *CollisionEntity, CollisionResult result) =0;
        virtual CollisionEntity *clone() =0;

        float dotProduct( vec2 one, vec2 two );
        std::vector<float> projectOnto( vec2 axis );
        std::pair<float,float> minMaxProjectOnto(vec2 axis);
        std::vector<vec2> getVertices();
        std::vector<vec2> getAxes();
        std::vector<vec2> getPerpAxes();
        std::vector<vec2> getNormedAxes();

    protected:
    private:
        float xvel;
        float yvel;
        bool onGround;
        COLLIDABLE cType;
        ColliderShapeType shapeType;
        CollisionShape shape;
};

#endif // COLLISIONENTITY_H
