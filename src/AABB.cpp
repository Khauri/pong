#include "engine/AABB.hpp"

bool AABB::isInside(float x_pos, float y_pos)
{
    return (x_pos >= x) && (x_pos <= x + w) && (y_pos >= y) && (y_pos <= y + h);
}

bool AABB::intersects(AABB box)
{
    return false;
}