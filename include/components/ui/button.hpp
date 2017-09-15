/**
* Simple Button Class
* Has 
*/
#ifndef UI_BTN_H
#define UI_BTN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "engine/AABB.hpp"
#include "engine/Actor.hpp"
#include "engine/Events.hpp"

class Button: public Actor{
    private:
        bool mouseover;
        bool mousedown;
        sf::Text btnText;
        sf::Font btnFont;
        std::string fontName;
        std::string text;
    public:
        Button();
        Button(AABB b, std::string t) : Actor(b), text(t){};
        //~Button();
        enum states {ACTIVE, INACTIVE, SELECTED, PRESSED};
        // do later? Sure
        void setText(std::string text);
        // user's methods
        void init();
        void onUpdate(int delta);
        void onRender(sf::RenderWindow* ctx);
};

#endif