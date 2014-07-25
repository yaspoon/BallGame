#ifndef EVENT_H
#define EVENT_H

#include "EventInput.h"
#include "EventCollision.h"
#include "EventSystem.h"

enum EventType
{
    EV_UNKNOWN = 0,
    EV_INPUT,
    EV_COLLISION,
    EV_SYSTEM
};

class Event
{
    public:
        Event();
        Event(EventInput newInput);
        Event(EventCollision newCollision);
        Event(EventSystem newSystem);
        virtual ~Event();
        EventType getType();
        void setType(EventType newType);
        EventInput getInput();
        void setInput(EventInput newInput);
        EventCollision getCollision();
        void setCollision(EventCollision newCollision);
    protected:
    private:
        EventType type;
        EventInput input;
        EventCollision collision;
        EventSystem system;
};

#endif // EVENT_H
