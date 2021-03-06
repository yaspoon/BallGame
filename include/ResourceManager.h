#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Resource.h"

class ResourceManager
{
    public:
        ResourceManager();
        virtual ~ResourceManager();
        int loadSurface(std::string filepath);
        int loadTexture(int resourceId);
        int loadTexture(std::string filepath);
        int loadText(std::string text);
        void unloadResource(int resource);
        Resource getResource(int resourceId);
        void initialise(); //Not great but it will work I hope...
    protected:
    private:
        std::vector<Resource> resources;
        std::map<std::string, int> resourcesMap;
        int resourceCount;
        SDL_Surface *internal_loadSurface(std::string filepath);
        SDL_Texture *internal_loadTexture(std::string filepath);
        SDL_Texture *internal_loadText(std::string text);
};

#endif // RESOURCEMANAGER_H
