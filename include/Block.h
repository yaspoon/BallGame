#ifndef BLOCKDEF
#define BLOCKDEF

#include "VisualEntity.h"

class Block: public VisualEntity
{

private:

//--------------------------------------Data

public:

//--------------------------------------Constructors/

    Block();

    Block( int flags, int width, int height, int bpp, float x, float y );

//--------------------------------------Destructors/
    virtual ~Block();

//--------------------------------------Methods/
    //------------------------------Accessors


    //------------------------------Mutators

    //------------------------------Imperita
    virtual void update( float dt );

    void collision( VisualEntity& collider );

};

#endif
