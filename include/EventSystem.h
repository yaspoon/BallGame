#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

#include "Event.h"

enum EventSystemType
{
        EV_SYS_UNKNOWN = 0,
        EV_SYS_QUIT
};

class EventSystem: public Event
{
    public:
        EventSystem();
        EventSystem(EventSystemType newType);
        virtual ~EventSystem();
        EventSystemType getSystemType();
    protected:
    private:
        EventSystemType type;
};

#endif // EVENTSYSTEM_H
