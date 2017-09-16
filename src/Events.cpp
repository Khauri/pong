#include <functional>
#include <string>
#include <queue>

#include "engine/Events.hpp"

Event::Event(const std::string m)
{ 
    message = m; 
};

std::string Event::getMessage()
{ 
    return message; 
};

EventBus::EventBus(){};

EventBus::~EventBus(){};

void EventBus::addEventListener(std::function<void (Event)> listener)
{ 
    listeners.push_back(listener); 
};

void EventBus::postEvent(Event e)
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