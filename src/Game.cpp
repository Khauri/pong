#include "engine/Game.hpp"
#include <iostream>

void Game::start()
{
    fpsTarget = 1000.00/fpsTarget;
    sf::Clock clock;
    int delta = 0;

    this->init();  
    // create game window
    window.create(sf::VideoMode(this->windowProps.width, this->windowProps.height), "Pong");
    
    // start main loop
    while(window.isOpen())
    {
        delta += clock.restart().asMilliseconds();
        // process events
        // TODO: Move to another function
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            switch(Event.type){
                case sf::Event::Closed:
                    this->exit();
                    break;
            }
        }
        
        if(delta < fpsTarget) continue;
        
        // notify of all events that took place last frame
        ebus.notify();
        
        // clear the screen
        window.clear(sf::Color::Black);
        // perform user updates
        this->onUpdate(delta);
        // update current screen (exits without error(?))
        //std::cout << currScreen->num << std::endl;
        this->currScreen->update(delta);
        // display
        this->currScreen->render(&window);

        window.display();

        // reset time since last frame
        delta = 0;
    }
}

// perform exit rituals and game cleanup
void Game::exit()
{
    this->onExit();
    window.close();
}

// for now just switches the two screens with no 
// transition 
void Game::goToScreen(std::shared_ptr<GameObj> s)
{
    s->game = this;
    s->addEventBus(&ebus);
    s->init();
    this->currScreen = s;
}

void Game::setDebugMode(bool b)
{
    this->debug = b;
}

bool Game::getDebugMode()
{
    return this->debug;
}