/**
* PONG
*
* The main pong executable
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "engine/Events.hpp"
#include "engine/Actor.hpp"
#include "components/ui/button.hpp"
#include "components/display/game.hpp"

// create the paddle actor class

// create the ball actor class

// create menu screen
class MainMenuScreen: public Actor
{
  public: 
    //std::shared_ptr<Button> sing = std::make_shared<Button>();
    //std::shared_ptr<Button> mult = std::make_shared<Button>();
    std::shared_ptr<Button> opts = std::make_shared<Button>();
    void init()
    {
      //this->addChild(sing);
      //this->addChild(mult);
      this->addChild(opts);
    }

    void onUpdate(int delta)
    {
      //std::cout << "updating screen: menu" << std::endl;
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
    void onUpdate(int delta)
    {
      std::cout << "updating screen: game" << std::endl;
    }
};

// create the game
class PongGame: public Game
{
  public:
    std::shared_ptr<MainMenuScreen> m = std::make_shared<MainMenuScreen>();
    void onUpdate(int delta)
    {
      //std::cout << "updating game" << std::endl;
    }

    void init()
    {
        std::cout << "initializing game" << std::endl;
        // add the all the shit
        //auto g = std::make_shared<GameScreen>();
        this->goToScreen(m);
    }
};


int main(int argc, char** argv)
{
  PongGame* p = new PongGame;
  p->start();
  delete p;
  return 0;
}
