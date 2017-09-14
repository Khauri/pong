#include <SFML/Graphics.hpp>
#include "components/display/game.hpp"
#include <iostream>
#include <memory>

void Game::start()
{
  this->init();  
  window.create(sf::VideoMode(this->windowProps.width, this->windowProps.height), "Pong");
  // start main loop
  while(window.isOpen())
  {
    // process events
    sf::Event Event;
    while(window.pollEvent(Event))
    {
      // Exit
      if(Event.type == sf::Event::Closed)
        window.close();
    }

    // clear screen and fill with red
    window.clear(sf::Color::Red);
    // perform user updates
    this->onUpdate(0);
    // update current screen (exits without error(?))
    std::cout << currScreen->num << std::endl;
    this->currScreen->update(0);
    // display
    window.display();
  }
}

// for now just switches the two screens with no 
// transition 
void Game::gotoScreen(Screen* s)
{
    //this->prevScreen = this->currScreen;
    this->currScreen = s;
}