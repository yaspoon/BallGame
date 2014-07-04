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
        Player();

        virtual ~Player();

        void update( float dt );

        void handleEvents( SDL_Event& event );

        void collision( VisualEntity& collider );

        void setYvel(float yvel);

    private:
        float xvel;
        float yvel;
        int moveSpeed;
};

#endif // _PLAYER_H__
