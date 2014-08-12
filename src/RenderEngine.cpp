#include "RenderEngine.h"
#include <SDL2/SDL.h>
#include "bgCommon.h"
#include "BallGame.h"

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
                if(TTF_Init() == -1)
                {
                    std::cout << "Failed to init TTF library TTF_ERROR:" << TTF_GetError() << std::endl;
                }
                else
                {
                    font = TTF_OpenFont("DejaVuSans-Bold.ttf", 18);
                }

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

void RenderEngine::draw(int sprite, SDL_Rect *src, SDL_Rect *dest)
{
    std::shared_ptr<ResourceManager> resourceManager = BALLGAME.getResourceManager();
    Resource spriteResource = resourceManager->getResource(sprite);

    switch(spriteResource.getType())
    {
        case RES_SURFACE:
        {
            SDL_Texture *tmp = SDL_CreateTextureFromSurface(renderer, spriteResource.getSurface());
            if(SDL_RenderCopy(renderer, tmp, src, dest) < 0)
            {
                std::cout << "Failed to copy texture SDL_Error:" << SDL_GetError() << std::endl;
            }
            SDL_DestroyTexture(tmp);
        }
        break;
        case RES_TEXT:
        case RES_TEXTURE:
        {
            if(SDL_RenderCopy(renderer, spriteResource.getTexture(), src, dest) < 0)
            {
                std::cout << "Failed to copy texture SDL_Error:" << SDL_GetError() << std::endl;
            }
        }
        break;
        case RES_AUDIO:
        break;
        case RES_UNKNOWN:
            std::cout << "ERROR:Resource type is unknown" << std::endl;
        break;
        default:
        break;
    }
}

void RenderEngine::show()
{
    SDL_RenderPresent(renderer);
}

void RenderEngine::setWindowTitle(std::string title)
{
    SDL_SetWindowTitle(mainWindow, title.c_str());
}

SDL_Renderer *RenderEngine::getRenderer()
{
    return renderer;
}

TTF_Font *RenderEngine::getFont()
{
    return font;
}

std::shared_ptr<SDL_Window*> RenderEngine::getWindow()
{
    return std::shared_ptr<SDL_Window*>(&mainWindow);
}

ScreenDimensions RenderEngine::getScreenDimensions()
{
    ScreenDimensions screenDim = {screenWidth, screenHeight};
    return screenDim;
}

void RenderEngine::setBackgroundColour(SDL_Color color)
{
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) != 0)
    {
        std::cout << "ERROR:Failed to set draw color SDL_Error:" << SDL_GetError() << std::endl;
    }
}

bool RenderEngine::toggleFullScreen()
{
    bool retval = false;
    Uint32 windowFlags = SDL_GetWindowFlags(mainWindow);
    windowFlags = windowFlags ^ SDL_WINDOW_FULLSCREEN_DESKTOP;
    if(SDL_SetWindowFullscreen(mainWindow, windowFlags) == 0)
    {
         retval = true;
    }

    return retval;
}
