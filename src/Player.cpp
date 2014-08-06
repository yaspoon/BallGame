/*
Project:
Author: Brock
*/

#include "Player.h"
#include <SDL2/SDL.h>
#include "BallGame.h"

Player::Player()
:CollisionEntity( "./images/ball.png", 0, 20, 40, 40, L_DEFAULT, CS_AABB)
{
    BALLGAME.getEventEngine()->registerForEvents(this, EV_INPUT);
    moveSpeed = 250;
    CollisionEntity::setCtype( C_MOVEABLE );
    CollisionShape shape;
    //shape.radius = 20.0f;
    shape.points.push_back((vec2){20, 0});
    shape.points.push_back((vec2){34.14, 5.85});
    shape.points.push_back((vec2){40, 20});
    shape.points.push_back((vec2){34.14, 34.14});
    shape.points.push_back((vec2){20, 40});
    shape.points.push_back((vec2){5.85, 34.14});
    shape.points.push_back((vec2){0, 20});
    shape.points.push_back((vec2){5.85, 5.85});
    CollisionEntity::setCollisionShape(shape);
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
    if(result.minAxis.y > 0) //Collison happened on y axis
    {
        if(result.minDistance < 0.0f)
        {
            setOnGround(true);
            setYvel(0.0f);
        }
        else
        {
            float newYvel = getYvel();
            newYvel = (newYvel > 0.0f) ? newYvel : -newYvel;
            setYvel(newYvel);
        }

    }
}

CollisionEntity *Player::clone()
{
    Player *tmp = new Player(*this);
    return (CollisionEntity*)tmp;
}

void Player::draw(RenderEngine renderEngine, vec2 offset)
{
    Rect posDim = getPosDim();
    SDL_Rect dest;
    ScreenDimensions screenDims = renderEngine.getScreenDimensions();
    SDL_Rect levelDimensions = BALLGAME.getCurrentLevel()->getLevelDimensions();

    if((posDim.x + (posDim.w / 2)) <= (screenDims.width / 2))
    {
        dest.x = (int)posDim.x;
        dest.y = (int)posDim.y;
        dest.w = (int)posDim.w;
        dest.h = (int)posDim.h;
    }
    else if((posDim.x + (posDim.w / 2)) >= levelDimensions.w - (screenDims.width / 2))
    {
        dest.x = (int)posDim.x - (levelDimensions.w - screenDims.width );
        dest.y = (int)posDim.y;
        dest.w = (int)posDim.w;
        dest.h = (int)posDim.h;
    }
    else
    {
        dest.x = (int)((screenDims.width / 2) - (posDim.w / 2));
        dest.y = (int)posDim.y;
        dest.w = (int)posDim.w;
        dest.h = (int)posDim.h;
    }

    renderEngine.draw(getSprite(), NULL, &dest);
}
