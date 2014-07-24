#ifndef EVENTENGINE_H
#define EVENTENGINE_H


class EventEngine
{
    public:
        EventEngine();
        virtual ~EventEngine();
        void processEvents();
        void addEvent();
    protected:
    private:
};

#endif // EVENTENGINE_H
