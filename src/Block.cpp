#include "Block.h"

//--------------------------------------Constructors/
    Block::Block()
    :CollisionEntity( "./images/block.bmp", 20.0f, 20.0f, 20.0f, 20.0f )
    {
        VisualEntity::setCtype( C_IMMOVABLE);

    }

    Block::Block( int flags, int width, int height, int bpp, float x, float y )
    :CollisionEntity( "./images/block.bmp", x, y, width, height )
    {
        VisualEntity::setCtype( C_IMMOVABLE );
    }

//--------------------------------------Destructors/
    Block::~Block()
    {

    }

//--------------------------------------Methods/
    //------------------------------Accessors

    //------------------------------Mutators

    //------------------------------Imperita
    void Block::update( float dt )
    {

    }

    void Block::collision( VisualEntity& collider )
    {

    }
