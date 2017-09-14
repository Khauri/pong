/**
* Button Class
*/
#ifndef UI_BTN_H
#define UI_BTN_H

#include "engine/Actor.hpp"

class Button: public Actor{
    Button(MessageBus* bus) : Actor(bus){};
};

#endif