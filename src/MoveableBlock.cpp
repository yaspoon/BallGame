#include "MoveableBlock.h"

MoveableBlock::MoveableBlock()
:Block()
{

}

MoveableBlock::MoveableBlock(std::string imagePath, int width, int height, float x, float y, LAYER drawingLayer, CollisionShape shape, vec2 direction, float velocity)
:Block(imagePath, width, height, x, y, drawingLayer, shape)
{
    this->direction = direction;
    setXvel(velocity);
    setYvel(velocity);
}

MoveableBlock::~MoveableBlock()
{
    //dtor
}

void MoveableBlock::update(float dt)
{
    Rect posDim = getPosDim();
    posDim.x = posDim.x + ((direction.x * getXvel()) * dt);
    posDim.y = posDim.y + ((direction.y * getYvel()) * dt);
    setPos(posDim.x, posDim.y);
}
