#include "EventSystem.h"

EventSystem::EventSystem()
{
    type = EV_SYS_UNKNOWN;
}

EventSystem::EventSystem(EventSystemType newType)
{
    type = newType;
}

EventSystem::~EventSystem()
{
    //dtor
}
