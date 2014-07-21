#ifndef RESOURCE_H
#define RESOURCE_H

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
    protected:
    private:
        int id;
        int count; //Number of objects holding a reference to this object
        ResourceType type;
};

#endif // RESOURCE_H
