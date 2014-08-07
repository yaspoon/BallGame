#include "ResourceManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL2/SDL_ttf.h>
#include "bgCommon.h"
#include "BallGame.h"

ResourceManager::ResourceManager()
{
    resourceCount = 0;
}

ResourceManager::~ResourceManager()
{
    //dtor
}

void ResourceManager::initialise()
{
}

int ResourceManager::loadSurface(std::string filepath)
{
    int retval = -1; //By default resource fails to load
    std::map<std::string, int>::iterator it = resourcesMap.find(filepath);
    if(it != resourcesMap.end()) //Resources potentialy already exists in map :3
    {
        Resource tmp = resources[it->second];
        if(tmp.getResourcePath().compare(filepath) == 0) //This is the same file
        {
            tmp.setReferenceCount(tmp.getReferenceCount() + 1);
            resources[it->second] = tmp;
            retval = tmp.getId();
        }
        else //This is not the same file but it hashed to the same address..
        {
            STUB("Well fuck we have a hashing collision...");
        }
    }
    else //resource doesnt exist so load it.
    {
        Resource newSurface;
        newSurface.setId(resourceCount);
        newSurface.setType(RES_SURFACE);
        newSurface.setResourcePath(filepath);
        newSurface.setReferenceCount(1);
        newSurface.setSurface(internal_loadSurface(filepath));
        if(newSurface.getSurface() != NULL) //Surface loaded succesfully
        {
            resources.push_back(newSurface);
            resourcesMap[filepath] = resourceCount;
            retval = resourceCount;
            resourceCount++;
        }
        else
        {
            std::cout << "Failed to load surface SDL_error:" << SDL_GetError() << std::endl;
        }
    }
    return retval;
}

/*
*This is only here to increment
*reference counters pretty much
*for when a Visual Entity gets copied
*/
int ResourceManager::loadTexture(int resourceId)
{
    int retval = -1;
    Resource tmp = resources[resourceId];
    if(tmp.getType() != RES_UNKNOWN)
    {
        tmp.setReferenceCount(tmp.getReferenceCount() + 1);
        resources[resourceId] = tmp;
        retval = resourceId;
    }
    return retval;
}

int ResourceManager::loadTexture(std::string filepath)
{
    int retval = -1;
    std::map<std::string, int>::iterator it = resourcesMap.find(filepath);
    if(it != resourcesMap.end()) //This resource has potentially already been loaded :3
    {
        Resource tmp = resources[it->second];
        if(tmp.getResourcePath().compare(filepath) == 0) //Same file path so same resource
        {
            tmp.setReferenceCount(tmp.getReferenceCount() + 1);
            resources[it->second] = tmp;
            retval = tmp.getId();
        }
        else
        {
            STUB("Well fuck we have a hashing collision...");
        }
    }
    else //Nope it don't exist yet :3
    {
        Resource newTexture;
        newTexture.setId(resourceCount);
        newTexture.setType(RES_TEXTURE);
        newTexture.setResourcePath(filepath);
        newTexture.setReferenceCount(1);
        newTexture.setTexture(internal_loadTexture(filepath));
        if(newTexture.getTexture() != NULL) //Successfully loaded texture hurrah
        {
            resources.push_back(newTexture);
            resourcesMap[filepath] = resourceCount;
            retval = resourceCount;
            resourceCount++;
        }
        else
        {
            std::cout << "Failed to load texture SDL_error:" << SDL_GetError() << std::endl;
        }
    }

    return retval;
}

int ResourceManager::loadText(std::string text)
{
    int retval = -1;
    std::map<std::string,int>::iterator it = resourcesMap.find(text);
    if(it != resourcesMap.end()) //Resource potentially exists in system
    {
        Resource tmp = resources[it->second];
        if(tmp.getResourcePath().compare(text) == 0)
        {
            tmp.setReferenceCount(tmp.getReferenceCount() + 1);
            resources[it->second] = tmp;
            retval = tmp.getId();
        }
        else
        {
            std::cout << "Hashing collision" << std::endl;
        }
    }
    else //Resource doesn't exist yet
    {
        Resource newText;
        newText.setId(resourceCount);
        newText.setType(RES_TEXT);
        newText.setResourcePath(text);
        newText.setReferenceCount(1);
        newText.setTexture(internal_loadText(text));
        if(newText.getTexture() != NULL)
        {
            resources.push_back(newText);
            resourcesMap[text] = resourceCount;
            retval = resourceCount;
            resourceCount++;
        }
        else
        {
            std::cout << "Error:Failed to load test SDL_Error:" << SDL_GetError() << std::endl;
        }
    }

    return retval;
}

void ResourceManager::unloadResource(int resource)
{
    Resource tmp = resources[resource];
    if(tmp.getReferenceCount() != 1)
    {
        tmp.setReferenceCount(tmp.getReferenceCount() - 1);
        resources[resource] = tmp;
    }
    else
    {
        switch(tmp.getType())
        {
            case RES_SURFACE:
                SDL_FreeSurface(tmp.getSurface());
                resources[resource] = Resource(); //Blank out resource
                resourcesMap.erase(tmp.getResourcePath());
            break;
            case RES_TEXTURE:
                SDL_DestroyTexture(tmp.getTexture());
                resources[resource] = Resource(); //Blank out resource
                resourcesMap.erase(tmp.getResourcePath());
            break;
            default:
            break;
        }
    }

}

Resource ResourceManager::getResource(int resourceId)
{
    return resources[resourceId];
}

SDL_Surface *ResourceManager::internal_loadSurface(std::string filepath)
{
    SDL_Surface* tmp = IMG_Load(filepath.c_str());

    if(tmp == NULL)
    {
        std::cout << "Failed to load image, loading default \"null\" texture SDL_Error:" << SDL_GetError() << std::endl;
        tmp = IMG_Load("images/null.png");
    }

    return tmp;
}

SDL_Texture *ResourceManager::internal_loadTexture(std::string filepath)
{
    SDL_Texture *retval = NULL;
    SDL_Surface *tmp = internal_loadSurface(filepath);
    if(tmp != NULL) //Hazzah didn't fail to load...
    {
        SDL_Renderer *renderer = BALLGAME.getRenderEngine().getRenderer();
        retval = SDL_CreateTextureFromSurface(renderer, tmp);
        SDL_FreeSurface(tmp);
    }
    else
    {
        std::cout << "Failed to load surface ultra gay SDL_Error:" << SDL_GetError() << std::endl;
    }

    return retval;
}

SDL_Texture *ResourceManager::internal_loadText(std::string text)
{
    SDL_Texture *retval = NULL;
    RenderEngine renderer = BALLGAME.getRenderEngine();
    SDL_Color color = (SDL_Color){255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Solid(renderer.getFont(), text.c_str(), color);

    if(tmp != NULL)
    {
        retval = SDL_CreateTextureFromSurface(renderer.getRenderer(), tmp);
        SDL_FreeSurface(tmp);
    }

    return retval;

}
