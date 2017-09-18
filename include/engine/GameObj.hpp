/**
* GameObj Class
* TODO
*   - Add ability to track game objects globally by a unique ID
*   - Add ability to remove game objects
*/

#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <list>
#include <memory>
#include "engine/AABB.hpp"
#include "engine/Events.hpp"

class Game; // forward declaration

class GameObj
{
    public:
        friend class Game;
        GameObj();
        GameObj(sf::Vector2f p) : pos(p) {};
        GameObj(AABB box) : bounds(box) {};
        // virtual user-defined game-running methods
        virtual void init(){};
        virtual void onUpdate(int delta){};
        virtual void onRender(sf::RenderWindow* ctx) {};
        // internal game-running methods
        void update(int delta);
        void render(sf::RenderWindow* ctx);
        // setters
        void setBounds(AABB b);
        void addChild(std::shared_ptr<GameObj> a);
        void setId(std::string id);
        // getters
        AABB getBounds();
        Game* game;
    protected:
        EventBus* ebus;
        AABB bounds;
        sf::Vector2f pos;
        std::list<std::shared_ptr<GameObj>> children;
        std::shared_ptr<GameObj> parent;
        void dispatchEvent(BasicEvent e);
        void addEventBus(EventBus* bus);
        std::function<void (BasicEvent)> getListener();
        virtual void onEvent(BasicEvent e){};
};

#include "engine/Game.hpp"

#endif