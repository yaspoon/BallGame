/*
Project:
Author: Brock
*/

#include "Player.h"
#include <SDL2/SDL.h>
#include "BallGame.h"

Player::Player()
:VisualEntity( "./images/ball.png", 0, 440, 40, 40 )
{
    xvel = 0;
    yvel = 0;
    moveSpeed = 250;
    onGround = false;
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

        }
        else if( yvel < 0 )
        {
            yvel += (320.0f * dt);

            tempPos.y += yvel * dt;
            tempPos.x += xvel * dt;
        }
        else
        {
            tempPos.y += yvel * dt;
            tempPos.x += xvel * dt;
        }

        VisualEntity::setPos( tempPos.x, tempPos.y );
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
                if(onGround)
                {
                    yvel = -180;
                    onGround = false;
                }
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

void Player::setYvel(float yvel)
{
    this->yvel = yvel;
}

float Player::getYvel()
{
    return yvel;
}

