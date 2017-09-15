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
    private:
        sf::Vector2f pos;
        const EventBus* ebus;
    public:
        Actor();
        virtual void init(){};
        // user's update method
        virtual void onUpdate(int delta) = 0;
        virtual void onRender(sf::RenderWindow* ctx) {};
        // internal update
        void update(int delta);
        void render(sf::RenderWindow* ctx);
        // setters
        void setPosition(sf::Vector2i p);
        void addChild(std::shared_ptr<Actor> a);
    protected:
        std::list<std::shared_ptr<Actor>> children;
        std::shared_ptr<Actor> parent;
        void dispatchEvent();
        virtual void onEvent(){};
        void addEventBus(EventBus* bus);
        // these may need to be virtual
};

#endif