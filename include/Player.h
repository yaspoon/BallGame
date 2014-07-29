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

    private:
        int moveSpeed;
};

#endif // _PLAYER_H__
