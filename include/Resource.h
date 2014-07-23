#ifndef RESOURCE_H
#define RESOURCE_H

#include <SDL2/SDL.h>
#include <string>

enum ResourceType
{
        RES_UNKNOWN = 0,
        RES_SURFACE,
        RES_TEXTURE,
        RES_AUDIO
};

class Resource
{
    public:
        Resource();
        virtual ~Resource();
        int getId();
        std::string getResourcePath();
        ResourceType getType();
        SDL_Surface *getSurface();
        SDL_Texture *getTexture();
        int getReferenceCount();
        void setId(int newId);
        void setType(ResourceType newType);
        void setSurface(SDL_Surface *newSurface);
        void setTexture(SDL_Texture *newTexture);
        void setReferenceCount(int refCount);
        void setResourcePath(std::string filepath);
    protected:
    private:
        int id;
        int references; //Number of objects holding a reference to this object
        ResourceType type;
        std::string resourcePath;
        union
        {
            SDL_Surface *surface;
            SDL_Texture *texture;
        } resource;
};

#endif // RESOURCE_H
