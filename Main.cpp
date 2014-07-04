#include "BallGame.h"
#include <SDL/SDL.h>
//#include <windows.h>

//--------------------------------Data/
BallGame* theBallGame;
int mainRetVal = 1;

//--------------------------------Methods/

int main( int argc, char* argv[] )
{
    mainRetVal = BALLGAME.ballGameMain();
    return mainRetVal;

}
