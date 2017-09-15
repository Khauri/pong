#include "engine/Actor.hpp"
#include "engine/Events.hpp"
#include <iostream>
#include <functional>
#include <list>
#include <memory>

Actor::Actor()
{
    
};

void Actor::update(int delta)
{
    // call user-defined update method
    this->onUpdate(delta);
    // call update method of all children
    for (auto a = children.begin(); a != children.end(); a++) {
        (*a)->update(delta);
    }
};

void Actor::render(sf::RenderWindow* ctx)
{
    // call user-defined render method
    this->onRender(ctx);
    // call render function of all children
    for(auto a = children.begin(); a != children.end(); a++){
        (*a)->render(ctx);
    }
}

void Actor::addChild(std::shared_ptr<Actor> a)
{
    // initialize the child
    a->game = game;
    a->init();
    // add the child to the list
    this->children.push_back(a);
    std::cout << "Adding a child" << std::endl;
};

void Actor::addEventBus(EventBus* bus)
{
    this->ebus = bus;
};