#ifndef RENDERENGINE_H
#define RENDERENGINE_H

#include <SDL2/SDL.h>

class RenderEngine
{
    public:
        RenderEngine();
        virtual ~RenderEngine();
        bool initialise();
        void clearScreen();
        //void draw(SDL_Texture sprite, SDL_Rect *src, SDL_Rect *dest);
        void show();
    protected:
    private:
        SDL_Renderer *renderer;
        SDL_Window *mainWindow;
};

#endif // RENDERENGINE_H
