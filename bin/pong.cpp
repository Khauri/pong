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
      if(bounds.x + radius >= 800){
        dispatchEvent(BasicEvent("P1_SCORED"));
        this->reset();
      }else if(bounds.x <= 0){
        dispatchEvent(BasicEvent("P2_SCORED"));
        this->reset();
      }
      // reverse the y-direction
      if(bounds.y < 0){
        bounds.y = 0;
        bounceY();
      }else if(bounds.y + radius >= 600){
        bounds.y = 600 - radius - 1;
        bounceY();
      }
      bounds.move(vel.x, vel.y); //move the ball hitbox with ball
      ball.move(vel.x, vel.y);
    }
    void onRender(sf::RenderWindow* ctx)
    {
      ctx->draw(ball);
    }
    // bounce the ball in x direction
    // increase the speed slightly
    void bounceX(){
      vel.x *= -1.01;
    }

    void bounceY()
    {
      vel.y *= -1;
    }
    // reset the ball
    void reset()
    {
      // pick a random x direction (-1 or 1)
      vel.x = std::round(rand() % 2 - 1);
      if(vel.x == 0) {
        vel.x = 1;
      }
      vel.y = (float) (rand()/((float)(RAND_MAX/(2))));

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
    float velMult = .1;
    int radius = 10;
};

// create the paddle(s)
class Paddle: public GameObj
{
  private:
    float speed = 0.1;
    std::shared_ptr<Ball> ball;
    bool isAIControlled = false;
    sf::RectangleShape paddle;
    sf::Keyboard::Key upKey;
    sf::Keyboard::Key downKey;
  public:
    Paddle(bool isAI, sf::Keyboard::Key u, sf::Keyboard::Key d, std::shared_ptr<Ball> b) :isAIControlled(isAI), upKey(u), downKey(d), ball(b)
    {

    }
    void init()
    {
      paddle.setSize(sf::Vector2f(bounds.w, bounds.h));
      this->setBounds(AABB(bounds.x, bounds.y, bounds.w, bounds.h));
      paddle.setFillColor(sf::Color::White);
      paddle.setPosition(bounds.x, bounds.y);
    }
    void onUpdate(int delta)
    {
      // check collision of ball
      if(this->bounds.isCollision(ball->getBounds())){
        ball->bounceX();
      }
      if(isAIControlled){
        AABB bPos = ball->getBounds();
        if(bPos.y < bounds.y ){
          if(this->bounds.y <= 0){
            return;
          }
          this->bounds.move(0, -speed);
        }else{
          if(this->bounds.y + this->bounds.h >= 600){
            return;
          }
          this->bounds.move(0, speed);
        }
      }
      else if(sf::Keyboard::isKeyPressed(upKey)){
        if(this->bounds.y <= 0){
          return;
        }
        this->bounds.move(0, -speed);
      }
      else if(sf::Keyboard::isKeyPressed(downKey)){
        if(this->bounds.y + this->bounds.h >= 600){
          return;
        }
        this->bounds.move(0, speed);
      }
      paddle.setPosition(bounds.x, bounds.y);
    }

    void onRender(sf::RenderWindow* ctx)
    {
      ctx->draw(paddle);
    }
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
      font->loadFromFile("../LCD_Solid.ttf"); //hard coded for now
      // create the text
      titlTxt = std::make_shared<BasicText>("BOONK", font);
      singTxt = std::make_shared<BasicText>("SINGLEPLAYER", font);
      multTxt = std::make_shared<BasicText>("MULTIPLAYER", font);
      optsTxt = std::make_shared<BasicText>("EXIT", font);
      // create the buttons
      titlTxt->setBounds(AABB(100.0, 200.0, 100.0, 50.0));
      singBtn = std::make_shared<Button>(singTxt, AABB(100.0, 300.0, 300.0, 50.0));
      multBtn = std::make_shared<Button>(multTxt, AABB(100.0, 400.0, 300.0, 50.0));
      optsBtn = std::make_shared<Button>(optsTxt, AABB(100.0, 500.0, 300.0, 50.0));

      this->addChild(titlTxt);
      this->addChild(singBtn);
      this->addChild(multBtn);
      this->addChild(optsBtn);
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
    bool isMultiplayer = false;
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<BasicText> scoreP2Text;
    std::shared_ptr<BasicText> scoreP1Text;
    std::shared_ptr<Paddle> p1;
    std::shared_ptr<Paddle> p2;
    void init()
    {
      font = std::make_shared<sf::Font>();
      font->loadFromFile("../LCD_Solid.ttf"); 

      scoreP1Text = std::make_shared<BasicText>("0", font);
      scoreP2Text = std::make_shared<BasicText>("0", font);
      scoreP1Text->setBounds(AABB(200, 50, 50, 50));
      scoreP2Text->setBounds(AABB(600, 50, 50, 50));

      ball = std::make_shared<Ball>();
      p1 = std::make_shared<Paddle>(false, sf::Keyboard::Up, sf::Keyboard::Down, ball);
      p1->setBounds(AABB(15, 250, 15, 100));

      if(isMultiplayer){
        p2 = std::make_shared<Paddle>(false, sf::Keyboard::W, sf::Keyboard::S, ball);
      }else{
        p2 = std::make_shared<Paddle>(true, sf::Keyboard::W, sf::Keyboard::S, ball);
      }
      p2->setBounds(AABB(770, 250, 15, 100));


      this->addChild(ball);
      this->addChild(scoreP1Text);
      this->addChild(scoreP2Text);
      this->addChild(p1);
      this->addChild(p2);
    }
    void onUpdate(int delta)
    {
    }
    void onEvent(BasicEvent e){
      std::string m = e.getMessage();
      if(m == "P1_SCORED"){
        scoreP1++;
        scoreP1Text->setText(std::to_string(scoreP1));
      }
      else if (m == "P2_SCORED"){
        scoreP2++;
        scoreP2Text->setText(std::to_string(scoreP2));
      }
      if(scoreP2 >= 11){
        this->dispatchEvent(BasicEvent("P2 WINS"));
      }
      if(scoreP1 >= 11){
        this->dispatchEvent(BasicEvent("P1 WINS"));
      }
    }
  private:
    int scoreP1 = 0;
    int scoreP2 = 0;
    std::shared_ptr<Ball> ball;
};
// doesn't currently work
class GameOverScreen: public GameObj
{
  public:
    std::shared_ptr<sf::Font> font;
    std::shared_ptr<BasicText> winner;
    //std::shared_ptr<Button> mainBtn;
    //std::shared_ptr<Button> multBtn;
    std::string text;
    GameOverScreen(std::string t) : text(t)
    {

    }
    void init()
    {
      font = std::make_shared<sf::Font>();
      font->loadFromFile("../LCD_Solid.ttf");
     // mainBtn = std::make_shared<Button>(std::make_shared<BasicText>())
    }
    void onUpdate(){

    }
    void onEvent(BasicEvent e)
    {

    }
};

// create the game
class PongGame: public Game
{
  public:
    std::shared_ptr<GameOverScreen> o;
    std::shared_ptr<MainMenuScreen> m;
    std::shared_ptr<GameScreen> g;
    
    void init()
    {
      //this->setDebugMode(true); // turn debug mode on and off
      m = std::make_shared<MainMenuScreen>();
      this->goToScreen(m);
    }
    
    void onUpdate(int delta)
    {
      
    }
    void onEvent(BasicEvent e)
    {
      std::string message = e.getMessage();
      if(message == "SINGLEPLAYER"){
        g = std::make_shared<GameScreen>();
        this->goToScreen(g);
      }
      else if(message == "MULTIPLAYER")
      {
        g = std::make_shared<GameScreen>();
        g->isMultiplayer = true;
        this->goToScreen(g);
      }
      else if(message == "P2 WINS")
      {
        o = std::make_shared<GameOverScreen>("P2 WINS");
        this->goToScreen(o);
      }
      else if(message == "P1 WINS")
      {
        o = std::make_shared<GameOverScreen>("P1 WINS");
        this->goToScreen(o);
      }
      else if(message == "EXIT")
      {
        this->exit();
      }
      else if(message == "MAIN")
      {
        m = std::make_shared<MainMenuScreen>();
        this->goToScreen(m);
      }
    }
};


int main(int argc, char** argv)
{
  PongGame p;
  p.start();
  return 0;
}
