#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

enum EventSystemType
{
        EV_SYS_UNKNOWN = 0,
        EV_SYS_QUIT
};

class EventSystem
{
    public:
        EventSystem();
        EventSystem(EventSystemType newType);
        virtual ~EventSystem();
    protected:
    private:
        EventSystemType type;
};

#endif // EVENTSYSTEM_H
