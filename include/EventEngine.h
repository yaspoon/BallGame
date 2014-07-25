#ifndef EVENTENGINE_H
#define EVENTENGINE_H

#include "Event.h"

class EventEngine
{
    public:
        EventEngine();
        virtual ~EventEngine();
        void processEvents();
        void addEvent(Event newEvent);
    protected:
    private:

};

#endif // EVENTENGINE_H
