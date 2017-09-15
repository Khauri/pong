#include "engine/Actor.hpp"
#include "engine/Events.hpp"
#include <iostream>
#include <functional>
#include <list>
#include <memory>
Actor::Actor()
{
    EventBus bus;
    this->ebus = &bus;
};

void Actor::update(int delta)
{
    std::cout << "updating actor" << std::endl;
    this->onUpdate(delta);
    // loop through children
    for (auto a = children.begin(); a != children.end(); a++) {
        // call child update function
        (*a)->update(delta);
    }
};

void Actor::addChild(actor_ptr a)
{
    this->children.push_back(a);
};

void Actor::addEventBus(EventBus* bus)
{
    this->ebus = bus;
};