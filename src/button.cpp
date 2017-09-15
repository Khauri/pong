#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "components/ui/button.hpp"

Button::Button() : Actor()
{
    text = "Button";
};

void Button::init()
{
    // load font
    btnFont.loadFromFile("../LCD_Solid.ttf");
    // set position
    btnText.setPosition(sf::Vector2f(bounds.x, bounds.y));
    // calculate bounding box
    btnText.setFont(btnFont);
    btnText.setString(text);
    btnText.setCharacterSize(30);
    btnText.setStyle(sf::Text::Bold);
    btnText.setColor(sf::Color::White);
    // button_shape
    

}
void Button::onUpdate(int delta)
{
    // kind of a hack but who cares(?)
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    if(bounds.isInside(mousePos.x, mousePos.y)){
        btnText.setColor(sf::Color::White);
        btnText.setCharacterSize(33);
        // recalculate bounding box
    }else{
        btnText.setColor(sf::Color(255,255,255,186));
        btnText.setCharacterSize(30);
    }
}

void Button::onRender(sf::RenderWindow* ctx)
{
    // Draw it
    // draw the text
    ctx->draw(btnText);

    // draw the bounding box
    if(false){
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(bounds.w, bounds.h));
        rectangle.setFillColor(sf::Color(0,0,0,0));
        rectangle.setOutlineColor(sf::Color::Yellow);
        rectangle.setOutlineThickness(5);
        rectangle.setPosition(bounds.x, bounds.y);
        ctx->draw(rectangle);
    }
    // draw the outline
}