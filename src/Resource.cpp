#include "Resource.h"
#include <string.h>

Resource::Resource()
{
    id = -1;
    references = 0;
    type = RES_UNKNOWN;
    resourcePath = "";
    memset(&resource, 0, sizeof(resource));
}

Resource::~Resource()
{
    //dtor
}

int Resource::getId()
{
    return id;
}

std::string Resource::getResourcePath()
{
    return resourcePath;
}

ResourceType Resource::getType()
{
    return type;
}

SDL_Surface *Resource::getSurface()
{
    return resource.surface;
}

SDL_Texture *Resource::getTexture()
{
    return resource.texture;
}

int Resource::getReferenceCount()
{
    return references;
}

void Resource::setId(int newId)
{
    id = newId;
}

void Resource::setType(ResourceType newType)
{
    type = newType;
}

void Resource::setSurface(SDL_Surface *newSurface)
{
    resource.surface = newSurface;
}

void Resource::setTexture(SDL_Texture *newTexture)
{
    resource.texture = newTexture;
}

void Resource::setReferenceCount(int refCount)
{
    references = refCount;
}

void Resource::setResourcePath(std::string filepath)
{
    resourcePath = filepath;
}
