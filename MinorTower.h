#ifndef MINORTOWER_H_INCLUDED
#define MINORTOWER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Tower.h"

class MinorTower : public Tower
{
public:
    MinorTower(double pos_x, double pos_y)
        : Tower(pos_x, pos_y)
    {
        attack_image = al_load_bitmap("./image/Tower/MinorTower_Beam.png");
        image = al_load_bitmap("./image/Tower/MinorTower.png");

        type = MAJOR_TOWER;
        width = al_get_bitmap_width(image);
        height = al_get_bitmap_width(image);;
        strcpy(name, "MinorTower");

        attack_range = 100;
        attack_frequency = 85;
        attack_harm_point = 3;
        attack_velocity = 5;

        circle->r = attack_range;
    }
};

#endif // MINORTOWER_H_INCLUDED

