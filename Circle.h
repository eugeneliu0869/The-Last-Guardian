#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

#include "global.h"

class Circle
{
public:
    Circle() {}
    Circle(int x, int y, int r)
    {
        this->x = x;
        this->y = y;
        this->r = r;
    }

    static bool isOverlap(Circle*, Circle*);

    double r;
    double x, y;
};

#endif // CIRCLE_H_INCLUDED
