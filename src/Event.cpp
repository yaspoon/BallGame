#include "Event.h"

Event::Event()
{
    type = EV_UNKNOWN;
}

Event::Event(EventInput newInput)
{
    type = EV_INPUT;
    input = newInput;
}

Event::Event(EventCollision newCollision)
{
    type = EV_COLLISION;
    collision = newCollision;
}

Event::Event(EventSystem newSystem)
{
    type = EV_SYSTEM;
    system = newSystem;
}

Event::~Event()
{
    //dtor
}

EventType Event::getType()
{
    return type;
}

void Event::setType(EventType newType)
{
    type = newType;
}

EventInput Event::getInput()
{
    return input;
}

void Event::setInput(EventInput newInput)
{
    input = newInput;
}

EventCollision Event::getCollision()
{
    return collision;
}

void Event::setCollision(EventCollision newCollision)
{
    collision = newCollision;
}
