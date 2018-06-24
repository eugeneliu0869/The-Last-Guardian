#ifndef MINORTOWER_H_INCLUDED
#define MINORTOWER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Tower.h"

class MinorTower : public Tower
{
public:
    MinorTower(double pos_x, double pos_y) : Tower(pos_x, pos_y)
    {
        sprite_num = 14;

        type = MINOR_TOWER;
        width = 38;
        height = 90;
        strcpy(name, "MinorTower");

        detect_range = 100;
        attack_range = 100;
        self_range = 30;

        attack_frequency = 80;
        attack_harm_point = 3;
        attack_velocity = 5;

        detect_circle->r = detect_range;
        attack_circle->r = attack_range;
        self_circle->r = self_range;

        attack_image = al_load_bitmap("./image/Tower/MinorTower/MinorTower_Beam.png");
        for(int i = 0; i<sprite_num; i++)
        {
            ALLEGRO_BITMAP* tmp;
            char buffer[50];

            sprintf(buffer, "./image/Tower/MinorTower/MinorTower_%d.png", i+1);
            tmp = al_load_bitmap(buffer);
            image_set.push_back(tmp);
        }
    }
};

#endif // MINORTOWER_H_INCLUDED
