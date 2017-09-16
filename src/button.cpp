#include <iostream>
#include "components/ui/button.hpp"

Button::Button() : GameObj()
{
};

void Button::setLabel(std::shared_ptr<BasicText> l)
{
    label = l;
}

void Button::init()
{
    this->addChild(label);
}

void Button::onUpdate(int delta)
{
    // kind of a hack but who cares(?)
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);
    if(bounds.isInside(mousePos.x, mousePos.y)){
        label->text.setColor(sf::Color::White);
        label->text.setCharacterSize(33);
        // recalculate bounding box
    }else{
        label->text.setColor(sf::Color(255,255,255,186));
        label->text.setCharacterSize(30);
    }
}

void Button::onRender(sf::RenderWindow* ctx)
{
    // manually call render function because hackssss
}

void Button::onEvent(Event e)
{
    std::cout << e.getMessage() << std::endl;
}