/*
Project:
Author: Brock
*/
#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "CollisionEntity.h"


class Player: public CollisionEntity
{
    public:
        Player();

        virtual ~Player();

        void update( float dt );

        void handleInputEvent(EventInput inputEvent);

        void handleSystemEvent(EventSystem systemEvent);
        void handleCollisionEvent(CollisionEntity *collisionEntity, CollisionResult result);
        CollisionEntity *clone();
        void draw(RenderEngine renderEngine, vec2 offset);

    private:
        int moveSpeed;
        int onGroundText;
};

#endif // _PLAYER_H__
