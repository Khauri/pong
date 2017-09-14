#ifndef ACTOR_H
#define ACTOR_H

#include "engine/Events"
#include <functional>

class Actor
{
    // TODO: find a way to skip supplying MessageBus
    //       perhaps use a factor(?)
    public:
        Actor(EventBus* bus);
        virtual void init();
        virtual void update();
    protected:
        EventBus* ebus;
        void dispatchEvent();
        virtual void onEvent();
};

#endif