#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SDL2/SDL.h>
#include <iostream>

class RenderEngine
{
    public:
        RenderEngine();
        virtual ~RenderEngine();
        bool initialise();
        void clearScreen();
        //void draw(SDL_Texture sprite, SDL_Rect *src, SDL_Rect *dest);
        void show();
        void setWindowTitle(std::string title);
    protected:
    private:
        SDL_Renderer *renderer;
        SDL_Window *mainWindow;
        int screenWidth;
        int screenHeight;
};

#endif // RENDERENGINE_H
