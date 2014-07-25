#ifndef EVENTENGINE_H
#define EVENTENGINE_H

#include "Event.h"
#include <vector>

class EventEngine
{
    public:
        EventEngine();
        virtual ~EventEngine();
        void processEvents();
        void addEvent(Event newEvent);
    protected:
    private:
        std::vector<Event> events;

};

#endif // EVENTENGINE_H
