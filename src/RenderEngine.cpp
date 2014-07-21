#include "RenderEngine.h"
#include <SDL2/SDL.h>
#include "bgCommon.h"

RenderEngine::RenderEngine()
{
    mainWindow = NULL;
    renderer = NULL;
}

RenderEngine::~RenderEngine()
{
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(mainWindow);
    mainWindow = NULL;
}

bool RenderEngine::initialise()
{
    bool retval = true;
    STUB("When in doubt stub it out");
    return retval;
}

void RenderEngine::clearScreen()
{
    SDL_RenderClear(renderer);
}

/*void RenderEngine::draw(SDL_Texture sprite, SDL_Rect *src, SDL_Rect *dest)
{
    SDL_RenderCopy(renderer, sprite, src, dest);
}*/

void RenderEngine::show()
{
    SDL_RenderPresent(renderer);
}
