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

class BasicEvent
{
    public: 
        int x;
        int y;
        BasicEvent(const std::string m);
        BasicEvent(const std::string m, int xpos, int ypos) : message(m), x(xpos), y(ypos){};
        std::string getMessage();
    private:
        std::string message;
};

class EventBus
{
    public:
        EventBus();
        ~EventBus();
        void addEventListener(std::function<void (BasicEvent)> listener);
        //void removeEventListener();
        void postEvent(BasicEvent e);
        void notify();
    private:
        std::list<std::function<void (BasicEvent)>> listeners;
        std::queue<BasicEvent> events;
};

#endif