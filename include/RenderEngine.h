#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SDL2/SDL.h>
#include <iostream>
#include <memory>
#include "ResourceManager.h"

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
        std::shared_ptr<SDL_Window*> getWindow();

    protected:
    private:
        SDL_Renderer *renderer;
        SDL_Window *mainWindow;
        int screenWidth;
        int screenHeight;
};

#endif // RENDERENGINE_H
