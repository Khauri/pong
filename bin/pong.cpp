/**
* PONG
*
* The main pong executable
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include "engine/Events.hpp"
#include "components/ui/button.hpp"
#include "components/display/game.hpp"
#include "engine/Actor.hpp"

// create the paddle actor class

// create the ball actor class

// create buttons

// create menu screen
class MainMenuScreen: public Actor
{
  public: 
    void init()
    {
      // create some buttons and some text
    }

    void onUpdate()
    {
      std::cout << "updating screen: menu" << std::endl;
    }
};
// create game screen
class GameScreen: public Actor
{
  public:
    void init()
    {
      std::cout << "Initialized" << std::endl;
    }
    void onUpdate()
    {
      std::cout << "updating screen: game" << std::endl;
    }
};
// create the game
class PongGame: public Game
{
  public:
    void onUpdate(int delta)
    {
      //std::cout << "updating game" << std::endl;
    }

    void init()
    {
        std::cout << "initializing game" << std::endl;
        // add the all the shit
        //MainMenuScreen m;
        GameScreen g;
        this->goToScreen(&g);
    }
};


int main(int argc, char** argv)
{
  PongGame p;
  p.start();
  return 0;
}
