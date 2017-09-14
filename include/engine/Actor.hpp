/**
* Actor Class
* Anything that's gonna be displayed on screen will inherit from here
* Actors can also function as containers for more actors
*/

#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <functional>
#include <list>
#include <memory>
#include "engine/Events.hpp"

class Actor
{
    // TODO: find a way to skip supplying MessageBus
    //       perhaps by using a factory(?)
    public:
        typedef std::shared_ptr<Actor> actor_ptr;
        Actor();
        Actor(EventBus* bus);
        virtual void init();
        // user's update method
        virtual void onUpdate(int delta){};
        // internal update
        virtual void update(int delta);
        virtual void render(){};
    protected:
        std::list<actor_ptr> children;
        std::shared_ptr<Actor> parent;
        const EventBus* ebus;
        void dispatchEvent();
        virtual void onEvent(){};
        // these may need to be virtual
        void addChild(actor_ptr a);
};

#endif