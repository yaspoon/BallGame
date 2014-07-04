/*
Project:
Author: Brock
*/

#include "Player.h"
#include <SDL/SDL.h>
#include "BallGame.h"

Player::Player()
:VisualEntity( "./images/ball2.png", 0, 440, 40, 40 )
{
    xvel = 0;
    yvel = 0;
    moveSpeed = 250;
    VisualEntity::setCtype( C_MOVEABLE );
}

Player::~Player()
{
    //dtor
}

void Player::update( float dt )
{
    Rect& tempPos = VisualEntity::getPosDim();

        if( yvel >= 0 )
        {
            yvel += (320.0f * dt);

            tempPos.y += yvel * dt;
            tempPos.x += xvel * dt;

            //Collision_t allowedMove = BALLGAME.checkMove( tempPos, yvel, xvel );

            VisualEntity::setPos( tempPos.x, tempPos.y );

        }
        else if( yvel < 0 )
        {
            yvel += (320.0f * dt);

            tempPos.y += yvel * dt;
            tempPos.x += xvel * dt;

            //Collision_t allowedMove = BALLGAME.checkMove( tempPos, yvel, xvel );

            VisualEntity::setPos( tempPos.x, tempPos.y );
        }
        else
        {
            tempPos.y += yvel * dt;
            tempPos.x += xvel * dt;

            //Collision_t allowedMove = BALLGAME.checkMove( tempPos, yvel, xvel );

            VisualEntity::setPos( tempPos.x, tempPos.y );
        }
}

void Player::handleEvents( SDL_Event& event )
{
    if( event.key.state == SDL_PRESSED )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                xvel = xvel - moveSpeed;
                break;
            case SDLK_RIGHT:
                xvel = xvel + moveSpeed;
                break;
            case SDLK_UP:
                yvel = -160;
                //VisualEntity::setPos( VisualEntity::getPosDim().x, VisualEntity::getPosDim().y - 1 );
                break;
            default:
                break;
        }
    }
    else if ( event.key.state == SDL_RELEASED )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_LEFT:
                    xvel = xvel + moveSpeed;
                break;
            case SDLK_RIGHT:
                    xvel = xvel - moveSpeed;
                break;
            default:
                break;
        }
    }
}

void Player::collision( VisualEntity& collider )
{

}

void Player::setYvel(float yvel)
{
    this->yvel = yvel;
}

