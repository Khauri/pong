#include <functional>
#include <string>
#include <queue>

#include "engine/Events.hpp"

BasicEvent::BasicEvent(const std::string m)
{ 
    message = m; 
};

std::string BasicEvent::getMessage()
{ 
    return message; 
};

EventBus::EventBus(){};

EventBus::~EventBus(){};

void EventBus::addEventListener(std::function<void (BasicEvent)> listener)
{ 
    listeners.push_back(listener); 
};

void EventBus::postEvent(BasicEvent e)
{ 
    events.push(e); 
};

void EventBus::notify()
{
    while(!events.empty()) {
        for (auto l = listeners.begin(); l != listeners.end(); l++) {
            (*l)(events.front());
        }
        events.pop();
    }
};