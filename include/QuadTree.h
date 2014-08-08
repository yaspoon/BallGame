#ifndef QUADTREE_H
#define QUADTREE_H

#include "CollisionEntity.h"

class QuadTree
{
    public:
        QuadTree(int level, SDL_Rect bounds);
        virtual ~QuadTree();
        void clear();
        void insert(CollisionEntity *collider);
        std::vector<CollisionEntity*> retrieve(std::vector<CollisionEntity*> objectList, CollisionEntity *collider);
    protected:
    private:
        int level;
        std::vector<CollisionEntity*> objects;
        SDL_Rect bounds;
        std::unique_ptr<QuadTree> nodes[4];
        const int MAX_OBJECTS = 5;
        const int MAX_LEVELS = 10;

        void split();
        int getIndex(CollisionEntity *collider);
};

#endif // QUADTREE_H
