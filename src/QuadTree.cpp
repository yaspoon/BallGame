#include "QuadTree.h"

QuadTree::QuadTree(int level, SDL_Rect bounds)
{
    this->level = level;
    this->bounds = bounds;
}

QuadTree::~QuadTree()
{
    for(int i = 0; i < 4; i++)
    {
        nodes[i].reset();
    }
}

void QuadTree::clear()
{
    objects.clear();
    for(int i = 0; i < 4; i++)
    {
        nodes[i]->clear();
        nodes[i].reset(NULL);
    }
}

void QuadTree::insert(CollisionEntity *collider)
{
    if(nodes[0].get() != NULL)
    {
        int index = getIndex(collider);

        if(index != -1)
        {
            nodes[index]->insert(collider);
            return;
        }
    }

    objects.push_back(collider);

    if(objects.size() > MAX_OBJECTS && level < MAX_LEVELS)
    {
        if(nodes[0].get() == NULL)
        {
            split();
        }

        int i = 0;
        while(i < objects.size())
        {
            int index = getIndex(objects[i]);
            if(index != -1)
            {
                nodes[index]->insert(objects[i]);
                objects.erase(objects.begin() + i);
            }
            else
            {
                i++;
            }
        }
    }
}

std::vector<CollisionEntity*> QuadTree::retrieve(std::vector<CollisionEntity*> objectList, CollisionEntity *collider)
{
    int index = getIndex(collider);
    if(index != -1 && nodes[0].get() != NULL)
    {
        std::vector<CollisionEntity*> tmp = nodes[index]->retrieve(objectList, collider);
        objectList.insert(objectList.end(), tmp.begin(), tmp.end());
    }

    objectList.insert(objectList.end(), objects.begin(), objects.end());

    return objectList;
}

void QuadTree::split()
{
    int subwidth = (int)(bounds.w / 2);
    int subheight = (int)(bounds.h / 2);
    int x = (int)bounds.x;
    int y = (int)bounds.y;

    SDL_Rect node1Bounds = {x, y, subwidth, subheight};
    nodes[0] = std::unique_ptr<QuadTree>(new QuadTree(level + 1, node1Bounds));

    SDL_Rect node2Bounds = {x + subwidth, y, subwidth, subheight};
    nodes[1] = std::unique_ptr<QuadTree>(new QuadTree(level + 1, node2Bounds));

    SDL_Rect node3Bounds = {x, y + subheight, subwidth, subheight};
    nodes[2] = std::unique_ptr<QuadTree>(new QuadTree(level + 1, node3Bounds));

    SDL_Rect node4Bounds = {x + subwidth, y = subheight, subwidth, subheight};
    nodes[3] = std::unique_ptr<QuadTree>(new QuadTree(level + 1, node4Bounds));
}

int QuadTree::getIndex(CollisionEntity *collider)
{
    int index = -1;
    Rect posDim = collider->getPosDim();
    int verticalMidpoint = bounds.w / 2;
    int horizontalMidpoint = bounds.y / 2;

    bool topQuadrant = posDim.y < horizontalMidpoint && posDim.y + posDim.h < horizontalMidpoint;
    bool bottomQuadrant = posDim.y > horizontalMidpoint && posDim.y + posDim.h > horizontalMidpoint;

    if(posDim.x < verticalMidpoint && posDim.x + posDim.w < verticalMidpoint)
    {
        if(topQuadrant)
        {
            index = 0;
        }
        else if(bottomQuadrant)
        {
            index = 2;
        }
    }
    else if(posDim.x > verticalMidpoint && posDim.x + posDim.w > verticalMidpoint)
    {
        if(topQuadrant)
        {
            index = 1;
        }
        else if(bottomQuadrant)
        {
            index = 3;
        }
    }

    return index;
}
