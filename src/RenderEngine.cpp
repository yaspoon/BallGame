#include "RenderEngine.h"
#include <SDL2/SDL.h>
#include "bgCommon.h"

RenderEngine::RenderEngine()
{
    mainWindow = NULL;
    renderer = NULL;
    screenWidth = 640;
    screenHeight = 480;
}

RenderEngine::~RenderEngine()
{
}

bool RenderEngine::initialise()
{
    bool retval = true;

    if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
    {
       std::cout << "Could not initialise SDL exiting! error:" << SDL_GetError() << std::endl;
    }
    else
    {

        mainWindow = SDL_CreateWindow("BallGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, 0 );
        if(mainWindow != NULL)
        {
            renderer = SDL_CreateRenderer(mainWindow, -1, 0);
            if(renderer != NULL)
            {
                std::cout << "Created window and renderer successfully" << std::endl;
                retval = true;
            }
            else
            {
                std::cout << "Failed to create renderer" << std::endl;
            }
        }
        else
        {
            std::cout << "Failed to create SDL Window" << std::endl;
        }

    }

    return retval;
}

bool RenderEngine::cleanup()
{
    bool retval = false;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(mainWindow);
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

void RenderEngine::setWindowTitle(std::string title)
{
    SDL_SetWindowTitle(mainWindow, title.c_str());
}
