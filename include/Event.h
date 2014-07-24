#ifndef EVENT_H
#define EVENT_H

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


};

#endif // EVENT_H
