#ifndef EVENT_H
#define EVENT_H

#include "EventInput.h"
#include "EventCollision.h"

enum EventType
{
    EV_UNKNOWN = 0,
    EV_INPUT,
    EV_COLLISION
};

class Event
{
    public:
        Event();
        virtual ~Event();
    protected:
    private:
        EventType type;
        union
        {
            EventInput input;
            EventCollision collision;
        };

};

#endif // EVENT_H
