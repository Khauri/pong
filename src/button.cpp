#include <iostream>
#include "components/ui/button.hpp"

void Button::init()
{
    // text
    btnFont.loadFromFile("../LCD_Solid.ttf");
    btnText.setFont(btnFont);
    btnText.setString("PONG");
    btnText.setCharacterSize(30);
    btnText.setStyle(sf::Text::Bold);
    btnText.setColor(sf::Color::White);
    // button_shape
    

}

void Button::onUpdate(int delta)
{
    //std::cout << "Updating button state" << std::endl;
}

void Button::onRender(sf::RenderWindow* ctx)
{
    // Draw it
    ctx->draw(btnText);
    // draw the text
    // draw the outline
}