#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <memory>
#include "ResourceManager.h"
#include "bgCommon.h"

class RenderEngine
{
    public:
        RenderEngine();
        virtual ~RenderEngine();
        bool initialise();
        void clearScreen();
        void draw(int sprite, SDL_Rect *src, SDL_Rect *dest);
        void show();
        void setWindowTitle(std::string title);
        bool cleanup();
        SDL_Renderer *getRenderer();
        TTF_Font *getFont();
        std::shared_ptr<SDL_Window*> getWindow();
        ScreenDimensions getScreenDimensions();
        void setBackgroundColour(SDL_Color color);
    protected:
    private:
        SDL_Renderer *renderer;
        SDL_Window *mainWindow;
        TTF_Font *font;
        int screenWidth;
        int screenHeight;
};

#endif // RENDERENGINE_H
