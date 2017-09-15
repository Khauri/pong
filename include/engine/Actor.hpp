/**
* Actor Class
* Anything that's gonna be displayed on screen will inherit from here
* Actors can also function as containers for more actors
*/

#ifndef ACTOR_H
#define ACTOR_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <list>
#include <memory>
#include "engine/Events.hpp"
#include "engine/AABB.hpp"
// forward declaration
class Game;

class Actor
{
    public:
        Actor();
        Actor(sf::Vector2f p) : pos(p) {};
        Actor(AABB box) : bounds(box) {};
        virtual void init(){};
        // user's update method
        virtual void onUpdate(int delta) = 0;
        virtual void onRender(sf::RenderWindow* ctx) {};
        // internal update
        void update(int delta);
        void render(sf::RenderWindow* ctx);
        // setters
        void setPosition(sf::Vector2f p);
        void addChild(std::shared_ptr<Actor> a);
        void setId(std::string id);
        Game* game;
    protected:
        const EventBus* ebus;
        AABB bounds;
        sf::Vector2f pos;
        std::list<std::shared_ptr<Actor>> children;
        std::shared_ptr<Actor> parent;
        void dispatchEvent();
        virtual void onEvent(){};
        void addEventBus(EventBus* bus);
        // these may need to be virtual
};
#include "components/display/game.hpp"
#endif