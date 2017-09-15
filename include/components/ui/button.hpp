/**
* Button Class
*/
#ifndef UI_BTN_H
#define UI_BTN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "engine/Actor.hpp"
#include "engine/Events.hpp"

class Button: public Actor{
    private:
        sf::Text btnText;
        sf::Font btnFont;
        sf::RectangleShape btnOutline;
        std::string fontName;
    public:
        //Button();
        //~Button();
        enum states {ACTIVE, INACTIVE, SELECTED, PRESSED};
        void init();
        void onUpdate(int delta);
        void onRender(sf::RenderWindow* ctx);
};

#endif