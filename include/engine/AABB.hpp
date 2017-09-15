/**
* Absolute Area Bounding Box
*/

#ifndef AABB_H
#define AABB_H

class AABB
{
    public:
        float x;
        float y;
        float w;
        float h;
        AABB() : x(0), y(0), w(0), h(0){};
        AABB(float x_pos, float y_pos, float width, float height) : x(x_pos), y(y_pos), w(width), h(height){};
        bool isInside(float x_pos, float y_pos);
        bool intersects(AABB box);
};


#endif