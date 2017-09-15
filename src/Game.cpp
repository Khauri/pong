#include <SFML/Graphics.hpp>
#include "components/display/game.hpp"
#include <iostream>
#include <memory>

void Game::start()
{
    std::cout << "Starting Game" << std::endl;

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
        sf::Event Event;
        while(window.pollEvent(Event))
        {
            // Exit
            if(Event.type == sf::Event::Closed)
            window.close();
        }
        
        if(delta < 1000.0/(this->fpsTarget)) continue;
        
        // clear screen and fill with red
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

// for now just switches the two screens with no 
// transition 
void Game::goToScreen(std::shared_ptr<Actor> s)
{
    //this->prevScreen = this->currScreen;
    s->init();
    this->currScreen = s;
    std::cout << "added screen" << std::endl;
}