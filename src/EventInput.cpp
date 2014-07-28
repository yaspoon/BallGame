#include "EventInput.h"

EventInput::EventInput()
{
    inputType = EV_INPUT_UNKNOWN;
}

EventInput::EventInput(EventInputType newType, InputKey newKey)
{
    inputType = newType;
    key = newKey;
}

EventInput::EventInput(EventInputType newType, InputController newController)
{
    inputType = newType;
    controller = newController;
}

EventInput::~EventInput()
{
    //dtor
}

EventInputType EventInput::getType()
{
    return inputType;
}

InputKey EventInput::getKey()
{
    return key;
}
