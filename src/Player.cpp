/*
Project:
Author: Brock
*/

#include "Player.h"
#include <SDL2/SDL.h>
#include "BallGame.h"

Player::Player()
:CollisionEntity( "./images/ball.png", 400, 20, 40, 40 )
{
    BALLGAME.getEventEngine()->registerForEvents(this, EV_INPUT);
    moveSpeed = 250;
    CollisionEntity::setCtype( C_MOVEABLE );
}

Player::~Player()
{
    BALLGAME.getEventEngine()->deregisterForEvents(this, EV_INPUT);
}

void Player::update( float dt )
{
    Rect& tempPos = VisualEntity::getPosDim();
    tempPos.y += CollisionEntity::getYvel() * dt;
    tempPos.x += CollisionEntity::getXvel() * dt;

    CollisionEntity::setYvel(CollisionEntity::getYvel() + (1000.0 * dt)); /*Gravity*/

    VisualEntity::setPos( tempPos.x, tempPos.y );
}

void Player::handleInputEvent(EventInput inputEvent)
{
    if(inputEvent.getType() == EV_INPUT_KEYDOWN)
    {
        switch(inputEvent.getKey())
        {
            case KEY_RIGHT:
                CollisionEntity::setXvel(CollisionEntity::getXvel() + moveSpeed);
            break;
            case KEY_LEFT:
                CollisionEntity::setXvel(CollisionEntity::getXvel() - moveSpeed);
            break;
            case KEY_JUMP:
                if(CollisionEntity::getOnGround())
                {
                    CollisionEntity::setYvel(-500.0);
                    CollisionEntity::setOnGround(false);
                }
            break;
            case KEY_UNKNOWN:
                break;
            default:
                break;

        }
    }
    else if(inputEvent.getType() == EV_INPUT_KEYUP)
    {
        switch(inputEvent.getKey())
        {
            case KEY_RIGHT:
                CollisionEntity::setXvel(CollisionEntity::getXvel() - moveSpeed);
            break;
            case KEY_LEFT:
                CollisionEntity::setXvel(CollisionEntity::getXvel() + moveSpeed);
            break;
            case KEY_UP:
            break;
            case KEY_DOWN:
            break;
            case KEY_JUMP:
            break;
            case KEY_UNKNOWN:
            break;
            default:
            break;
        }
    }
}

void Player::handleSystemEvent(EventSystem system)
{
    switch(system.getType())
    {
        case EV_SYS_QUIT:
        case EV_SYS_UNKNOWN:
        default:
            break;
    }
}

void Player::handleCollisionEvent(CollisionEntity *collisionEntity, CollisionResult result)
{
    collisionEntity = NULL;
}

CollisionEntity *Player::clone()
{
    Player *tmp = new Player(*this);
    return (CollisionEntity*)tmp;
}
