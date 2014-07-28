#ifndef EVENT_H
#define EVENT_H

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
        Event(EventType newType);
        virtual ~Event();
        EventType getType();
    protected:
    private:
        EventType type;
};

#endif // EVENT_H
