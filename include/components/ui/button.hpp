/**
* Button Class
*/
#ifndef UI_BTN_H
#define UI_BTN_H

#include "engine/Actor.hpp"
#include "engine/Events.hpp"

class Button: public Actor{
    public:
        Button();
        ~Button();
        enum states {ACTIVE, INACTIVE, SELECTED, PRESSED};
        void init();
};

#endif