#include <iostream>
#include "engine/Game.hpp"
#include "engine/Events.hpp"

void Game::start()
{
    double fps = 60.0;
    sf::Vector2i mousePos;
    this->ebus.addEventListener(this->getListener());
    sf::Clock clock;
    int delta;

    this->init();  
    // create game window
    window.create(sf::VideoMode(this->windowProps.width, this->windowProps.height), "Pong", sf::Style::Titlebar | sf::Style::Close);
    
    // start main loop
    while(window.isOpen())
    {
        delta = clock.restart().asMilliseconds();
        mousePos = sf::Mouse::getPosition(window);
        // process events
        // TODO: Move to another function
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            switch(Event.type){
                case sf::Event::Closed:
                    this->exit();
                    break;
                case sf::Event::MouseButtonReleased:
                    this->ebus.postEvent(BasicEvent("MOUSEUP", mousePos.x, mousePos.y));
                    break;
            }
        }

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

void Game::dispatchEvent(BasicEvent e)
{
    ebus.postEvent(e);
};

std::function<void (BasicEvent)> Game::getListener()
{
    auto listener = [=](BasicEvent e) -> void {
        this->onEvent(e);
    };
    return listener;
};