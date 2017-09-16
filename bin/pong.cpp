/**
* PONG
*
* The main pong executable
* (It's a lot more complex than it should be)
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <cmath>
#include "engine/Engine.hpp"
#include "components/ui/button.hpp"
#include "components/ui/text.hpp"


// create the paddle(s)

// create the ball
class Ball: public GameObj
{
  public:
    void init()
    {
      ball.setRadius(radius);
      this->reset();
    }
    void onUpdate(int delta)
    {
      // Update score and reset 
      if(bounds.x >= 800){
        dispatchEvent(Event("P1_SCORED"));
        this->reset();
      }else if(bounds.x < 0 - radius){
        dispatchEvent(Event("P2_SCORED"));
        this->reset();
      }
      // reverse the y-direction
      if(bounds.y < 0 || bounds.y + radius >= 600){
        vel.y *= -1;
      }

      bounds.move(vel.x, vel.y); //move the ball hitbox with ball
      ball.move(vel.x, vel.y);
    }
    void onRender(sf::RenderWindow* ctx)
    {
      ctx->draw(ball);
    }
    // bounce the ball and 
    void bounce(){
      
    }
    // reset the ball
    void reset()
    {
      // pick a random x direction (-1 or 1)
      vel.x = std::round(rand() % 2 - 1);
      if(vel.x == 0) {vel.x = 1;}
      vel.y = rand() % 2 - 1;

      // set initial velocity of ball
      vel.x *= velMult;
      vel.y *= velMult;
      // set Initial position and Width/Height of the ball in exact center of screen
      this->setBounds(AABB(400 - radius/2.0, 300 - radius/2.0, radius*2, radius*2));
      ball.setPosition(bounds.x, bounds.y);
    }
  private:
    sf::CircleShape ball;
    sf::Vector2f vel;
    float velMult = 4.0;
    int radius = 10;
};
// create menu screen
class MainMenuScreen: public GameObj
{
  public:
    std::shared_ptr<sf::Font> font;
    // buttons
    std::shared_ptr<Button> singBtn;
    std::shared_ptr<Button> multBtn;
    std::shared_ptr<Button> optsBtn;
    // some text
    std::shared_ptr<BasicText> titlTxt;
    std::shared_ptr<BasicText> singTxt;
    std::shared_ptr<BasicText> multTxt;
    std::shared_ptr<BasicText> optsTxt;
    
    void init()
    {
      font = std::make_shared<sf::Font>();
      font->loadFromFile("../LCD_Solid.tff"); //hard coded for now
      // create the text
      titlTxt = std::make_shared<BasicText>("BOONK", font);
      singTxt = std::make_shared<BasicText>("SINGLEPLAYER", font);
      multTxt = std::make_shared<BasicText>("MULTIPLAYER");
      optsTxt = std::make_shared<BasicText>("OPTIONS");
      // create the buttons
      singBtn = std::make_shared<Button>(singTxt);
      multBtn = std::make_shared<Button>(multTxt);
      optsBtn = std::make_shared<Button>(optsTxt);

      this->addChild(titlTxt);
      this->addChild(singBtn);
      //this->addChild(multBtn);
      //this->addChild(optsBtn);
    }

    void onUpdate(int delta)
    {
      //std::cout << "updating screen: menu" << std::endl;
    }
};
// create game screen
class GameScreen: public GameObj
{
  public:
    void init()
    {
      ball = std::make_shared<Ball>();
      this->addChild(ball);
    }
    void onUpdate(int delta)
    {
    }
    void onEvent(Event e){
      std::string m = e.getMessage();
      if(m == "P1_SCORED"){
          scoreP1++;
      }
      else if (m == "P2_SCORED"){
          scoreP2++;
      }
      printf("Score: %d %d\n", scoreP1, scoreP2);
    }
  private:
    int scoreP1 = 0;
    int scoreP2 = 0;
    std::shared_ptr<Ball> ball;
};

// create the game
class PongGame: public Game
{
  public:
    std::shared_ptr<MainMenuScreen> m;
    std::shared_ptr<GameScreen> g;
    
    void init()
    {
      m = std::make_shared<MainMenuScreen>();
      g = std::make_shared<GameScreen>();
      //this->setDebugMode(true); // turn debug mode on and off
      this->goToScreen(g);
    }
    
    void onUpdate(int delta)
    {
      
    }
};


int main(int argc, char** argv)
{
  PongGame p;
  p.start();
  return 0;
}
