/**
* Absolute Area Bounding Box
* Can also be used as a hitbox
*/

#ifndef AABB_H
#define AABB_H

#include <SFML/Graphics.hpp>

class AABB
{
    private:
        sf::RectangleShape rect;
    public:
        float x;
        float y;
        float w;
        float h;
        AABB() : x(0), y(0), w(0), h(0){};
        AABB(float x_pos, float y_pos, float width, float height) : x(x_pos), y(y_pos), w(width), h(height){};
        bool isInside(float x_pos, float y_pos);
        bool isCollision(AABB box);
        bool intersects(AABB box);
        void render(sf::RenderWindow* ctx);
        void move(float x, float y);
        void setPosition(float x, float y);
        void setWidth(float w);
        void setHeight(float h);
};


#endif