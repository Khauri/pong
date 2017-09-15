/**
* Game.hpp
* A Game manages both the main game loop. game state as well as
* the eventbus, processes, global flags, window, and other shit
*/
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "engine/Actor.hpp"
#include "engine/Events.hpp"

typedef struct
{
    int x;
    int y;
    int width;
    int height;
} BOX;

class Game{
    public:
        void start();
        void stop();
        void exit();
        virtual void onUpdate(int delta){};
        void goToScreen(std::shared_ptr<Actor> s);
        // init is automatically called when game is started
        virtual void init(){};
        // TODO
        void setResizable(bool r);
        void setSize(int w, int y);
        bool toggleFullScreen();
    protected:
        sf::RenderWindow window;
        EventBus ebus;
        std::shared_ptr<Actor> currScreen;
        //std::shared_ptr<Screen> prevScreen;
    private: 
        float fpsTarget = 60;
        float actualFps;
        BOX windowProps {0,0,800,600};
};

#endif