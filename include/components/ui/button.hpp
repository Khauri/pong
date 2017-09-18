/**
* Simple Button Class
* Has 
*/
#ifndef UI_BTN_H
#define UI_BTN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include "engine/Engine.hpp"
#include "components/ui/text.hpp"

class Button: public GameObj
{
    private:
        std::shared_ptr<BasicText> label;
    public:
        Button();
        Button(std::shared_ptr<BasicText> l, AABB box);
        //~Button();
        void setLabel(std::shared_ptr<BasicText> l);
        // user's methods
        void init();
        void onUpdate(int delta);
        void onRender(sf::RenderWindow* ctx);
        void onEvent(BasicEvent e);
};

#endif