/**
* Simple Text Class(es)
* Simply defines a bounding box 
*/
#ifndef UI_TXT_H
#define UI_TXT_H

#include <SFML/Graphics.hpp>
#include <string>
#include "engine/Engine.hpp"

class BasicText: public GameObj
{
    public:
        sf::Text text;
        enum ALIGN {START, MIDDLE, END};
        BasicText();
        BasicText(std::string t) : str(t){};
        BasicText(std::string t, std::shared_ptr<sf::Font> f) : str(t), font(f){};
        //~BasicText();
        void setText(std::string t);
        std::string getText();
        void setVerticalAlign(ALIGN a);
        void setHorizontalAlign(ALIGN a);
        // user's methods
        void init();
        void onUpdate(int delta);
        void onRender(sf::RenderWindow* ctx);
    private:
        std::shared_ptr<sf::Font> font;
        std::string str;
        ALIGN v;
        ALIGN h;
};

#endif