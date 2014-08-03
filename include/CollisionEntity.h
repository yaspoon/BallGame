#ifndef COLLISIONENTITY_H
#define COLLISIONENTITY_H

#include "VisualEntity.h"
#include "bgCommon.h"

class CollisionEntity: public VisualEntity
{
    public:
        CollisionEntity();
        CollisionEntity(std::string filename, float x, float y, float width, float height);
        virtual ~CollisionEntity();
        float getXvel();
        float getYvel();
        bool getOnGround();
        COLLIDABLE getCtype();
        void setXvel(float newVel);
        void setYvel(float newVel);
        void setOnGround(bool isOnGround);
        void setCtype(COLLIDABLE type);
        virtual void handleCollisionEvent(CollisionEntity *CollisionEntity, CollisionResult result) =0;
        virtual CollisionEntity *clone() =0;
    protected:
    private:
        float xvel;
        float yvel;
        bool onGround;
        COLLIDABLE cType;
};

#endif // COLLISIONENTITY_H
