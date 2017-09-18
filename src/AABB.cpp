#include "engine/AABB.hpp"

bool AABB::isInside(float x_pos, float y_pos)
{
    return (x_pos >= x) && (x_pos <= x + w) && (y_pos >= y) && (y_pos <= y + h);
}

void AABB::move(float x, float y)
{
    this->x+=x;
    this->y+=y;
}

void AABB::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void AABB::setWidth(float w)
{
    this->w = w;
}

void AABB::setHeight(float h)
{
    this->h = h;
}

bool AABB::isCollision(AABB box)
{
    return x < box.x + box.w && 
        x + w > box.x &&
        y < box.y + box.w &&
        h + y > box.y;
}

bool AABB::intersects(AABB box)
{
    return false;
}
// Draw the bounding box
void AABB::render(sf::RenderWindow* ctx)
{
    rect.setPosition(x, y);
    rect.setSize(sf::Vector2f(w, h));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineColor(sf::Color::Yellow);
    rect.setOutlineThickness(3);
    ctx->draw(rect);
}