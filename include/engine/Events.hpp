/**
* Basic EventBus system adapted from this tutorial:
* http://www.seanballais.com/blog/implementing-a-simple-message-bus-in-cpp/
*/

#ifndef EVENTM_H
#define EVENTM_H

#include <queue>
#include <list>
#include <string>
#include <functional>

class Event
{
    public: 
        Event(const std::string m);
        std::string getMessage();
    private:
        std::string message;
};

class EventBus
{
    public:
        EventBus();
        ~EventBus();
        void addEventListener(std::function<void (Event)> listener);
        //void removeEventListener();
        void postEvent(Event e);
        void notify();
    private:
        std::list<std::function<void (Event)>> listeners;
        std::queue<Event> events;
};

#endif