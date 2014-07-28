#ifndef EVENTINPUT_H
#define EVENTINPUT_H

enum EventInputType
{
    EV_INPUT_UNKNOWN = 0,
    EV_INPUT_KEYDOWN,
    EV_INPUT_KEYUP,
    EV_CONTROLLER_BUTTON_DOWN,
    EV_CONTROLLER_BUTTON_UP
};

enum InputKey
{
    KEY_UNKNOWN = 0,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_UP,
    KEY_DOWN,
    KEY_JUMP
};

enum InputController
{
    CON_UNKNOWN = 0,
    CON_LEFT,
    CON_RIGHT,
    CON_UP,
    CON_DOWN
};

class EventInput
{
    public:
        EventInput();
        EventInput(EventInputType newType, InputKey newKey);
        EventInput(EventInputType newType, InputController newController);
        virtual ~EventInput();
        EventInputType getType();
        InputKey getKey();
    protected:
    private:
        EventInputType inputType;
        InputKey key;
        InputController controller;

};

#endif // EVENTINPUT_H
