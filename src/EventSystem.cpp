#include "EventSystem.h"

EventSystem::EventSystem()
:Event(EV_SYSTEM)
{
    type = EV_SYS_UNKNOWN;
}

EventSystem::EventSystem(EventSystemType newType)
:Event(EV_SYSTEM)
{
    type = newType;
}

EventSystem::~EventSystem()
{
    //dtor
}

EventSystemType EventSystem::getSystemType()
{
    return type;
}
