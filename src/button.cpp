#include <iostream>
#include "components/ui/button.hpp"

Button::Button() : GameObj()
{
};

Button::Button(std::shared_ptr<BasicText> l, AABB box) : GameObj(box){
    this->setLabel(l);
};

void Button::setLabel(std::shared_ptr<BasicText> l)
{
    label = l;
    l->setBounds(this->bounds);
}

void Button::init()
{
    this->addChild(label);
}

void Button::onUpdate(int delta)
{
    // TODO:
    // Instead of checking the mouse events here, check them elsewhere
    sf::Vector2i mousePos = sf::Mouse::getPosition(game->window);

    if(bounds.isInside(mousePos.x, mousePos.y)){
        label->text.setColor(sf::Color::White);
        label->text.setCharacterSize(33);
    }else{
        label->text.setColor(sf::Color(255,255,255,186));
        label->text.setCharacterSize(30);
    }
}

void Button::onRender(sf::RenderWindow* ctx)
{
    // manually call render function because hackssss
}

void Button::onEvent(BasicEvent e)
{
    if(e.getMessage() == "MOUSEUP"){
        if(bounds.isInside(e.x, e.y)){
            dispatchEvent(BasicEvent(label->getText()));
        }
    }
}