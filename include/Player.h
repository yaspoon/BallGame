/*
Project:
Author: Brock
*/
#ifndef _PLAYER_H__
#define _PLAYER_H__

#include "VisualEntity.h"


class Player: public VisualEntity
{
    public:
        bool onGround;
        Player();

        virtual ~Player();

        void update( float dt );

        void handleInputEvent(EventInput inputEvent);

        void setYvel(float yvel);

        float getYvel();

    private:
        float xvel;
        float yvel;
        int moveSpeed;
};

#endif // _PLAYER_H__
