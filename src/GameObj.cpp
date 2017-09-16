#include "engine/GameObj.hpp"
#include <iostream>

GameObj::GameObj()
{
    
};

void GameObj::update(int delta)
{
    // call user-defined update method
    this->onUpdate(delta);
    // call update method of all children
    for (auto a = children.begin(); a != children.end(); a++) {
        (*a)->update(delta);
    }
};

void GameObj::render(sf::RenderWindow* ctx)
{
    // call user-defined render method
    this->onRender(ctx);
    // call render function of all children
    for(auto a = children.begin(); a != children.end(); a++){
        (*a)->render(ctx);
    }
    // draw the bounding box in debug mode
    if(game->getDebugMode()){
        bounds.render(ctx);
    }
}

void GameObj::addChild(std::shared_ptr<GameObj> a)
{
    // initialize the child
    a->game = game;
    a->addEventBus(ebus);
    a->init();
    // add the child to the list
    this->children.push_back(a);
};

void GameObj::addEventBus(EventBus* bus)
{
    this->ebus = bus;
    this->ebus->addEventListener(this->getListener());
};

void GameObj::dispatchEvent(Event e)
{
    ebus->postEvent(e);
};

std::function<void (Event)> GameObj::getListener()
{
    auto listener = [=](Event e) -> void {
        this->onEvent(e);
    };
    return listener;
};

void GameObj::setBounds(AABB b)
{
    this->bounds = b;
}