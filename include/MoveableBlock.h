#ifndef MOVEABLEBLOCK_H
#define MOVEABLEBLOCK_H

#include "Block.h"

class MoveableBlock: public Block
{
    public:
        MoveableBlock();
        MoveableBlock(std::string imagePath, int width, int height, float x, float y, LAYER drawingLayer, CollisionShape shape, vec2 direction, float velocity);
        virtual ~MoveableBlock();
        void update(float dt);
    protected:
    private:
        vec2 direction;
};

#endif // MOVEABLEBLOCK_H
