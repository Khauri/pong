#include <iostream>
#include "components/ui/text.hpp"

BasicText::BasicText() : GameObj()
{
    str = "Undefined";
};

void BasicText::init()
{   
    
    text.setString(str);
    text.setFont(*font);
    //TODO: Calculate Position 
    text.setPosition(sf::Vector2f(bounds.x, bounds.y));
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Bold);
    text.setColor(sf::Color::White);
}

void BasicText::onUpdate(int delta)
{
    
}

void BasicText::onRender(sf::RenderWindow* ctx)
{
    // draw the label
    ctx->draw(this->text);
}