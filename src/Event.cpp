#include "Event.h"

Event::Event()
{
    type = EV_UNKNOWN;
}

Event::Event(EventType newType)
{
    type = newType;
}

Event::~Event()
{
    //dtor
}

EventType Event::getType()
{
    return type;
}
