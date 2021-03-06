#ifndef BLOCKDEF
#define BLOCKDEF

#include "CollisionEntity.h"

class Block: public CollisionEntity
{

private:

//--------------------------------------Data

public:

//--------------------------------------Constructors/

    Block();

    Block(int width, int height, float x, float y, LAYER drawingLayer);
    Block(int width, int height, float x, float y, LAYER drawingLayer, CollisionShape shape);
    Block(std::string imagePath, int width, int height, float x, float y, LAYER drawingLayer);
    Block(std::string imagePath, int width, int height, float x, float y, LAYER drawingLayer, CollisionShape shape);

//--------------------------------------Destructors/
    virtual ~Block();

    void update(float dt) {dt=0;}
    void handleInputEvent(EventInput input);
    void handleSystemEvent(EventSystem system);
    void handleCollisionEvent(CollisionEntity *collision, CollisionResult result);
    CollisionEntity *clone();

};

#endif
