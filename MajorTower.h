#ifndef MAJORTOWER_H_INCLUDED
#define MAJORTOWER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Tower.h"

class MajorTower : public Tower
{
public:
    MajorTower(double pos_x, double pos_y)
        : Tower(pos_x, pos_y)
    {
        attack_image = al_load_bitmap("./image/Tower/MajorTower_Beam.png");
        image = al_load_bitmap("./image/Tower/MajorTower.png");

        type = MAJOR_TOWER;
        width = al_get_bitmap_width(image);
        height = al_get_bitmap_width(image);;
        strcpy(name, "MajorTower");

        attack_range = 150;
        attack_frequency = 50;
        attack_harm_point = 5;
        attack_velocity = 7;

        circle->r = attack_range;
    }
};

#endif // MAJORTOWER_H_INCLUDED
