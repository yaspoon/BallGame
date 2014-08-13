#ifndef EVENTENGINE_H
#define EVENTENGINE_H

#include "EventSystem.h"
#include "EventCollision.h"
#include "Entity.h"
#include "CollisionEntity.h"
#include <vector>
#include <map>
#include <SDL2/SDL.h>

class EventEngine
{
    public:
        EventEngine();
        virtual ~EventEngine();
        void generateEvents();
        void processEvents();
        void addEvent(Event newEvent);
        void addCollisionEvent(EventCollision collision);
        std::vector<EventSystem> getSystemEvents();
        std::vector<EventInput> getInputEvents();
        std::vector<EventCollision> getCollisionEvents();
        void clearEventQueues();
        bool registerForEvents(Entity *entityToReg, EventType typeToReg);
        bool deregisterForEvents(Entity *entityToDeReg, EventType typeToDeReg);
    protected:
    private:
        std::vector<EventSystem> systemEvents;
        std::vector<EventInput> inputEvents;
        std::vector<EventCollision> collisionEvents;

        std::vector<Entity*> systemEventEntities;
        std::vector<Entity*> inputEventEntities;
        std::vector<CollisionEntity*> collisionEventEntities;

        std::map<InputKey, SDL_Scancode> inputMap;
        std::map<EventSystemType, SDL_Scancode> systemMap;

};

#endif // EVENTENGINE_H
