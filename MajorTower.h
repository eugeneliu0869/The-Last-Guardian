#ifndef MAJORTOWER_H_INCLUDED
#define MAJORTOWER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Tower.h"

class MajorTower : public Tower
{
public:
    MajorTower(double pos_x, double pos_y) : Tower(pos_x, pos_y)
    {
        sprite_num = 14;

        type = MAJOR_TOWER;
        width = 38;
        height = 90;
        strcpy(name, "MajorTower");

        detect_range = 150;
        attack_range = 150;
        self_range = 50;

        attack_frequency = 50;
        attack_harm_point = 5;
        attack_velocity = 7;

        detect_circle->r = detect_range;
        attack_circle->r = attack_range;
        self_circle->r = self_range;

        attack_image = al_load_bitmap("./image/Tower/MajorTower/MajorTower_Beam.png");
        for(int i = 0; i<sprite_num; i++)
        {
            ALLEGRO_BITMAP* tmp;
            char buffer[50];

            sprintf(buffer, "./image/Tower/MajorTower/MajorTower_%d.png", i+1);
            tmp = al_load_bitmap(buffer);
            image_set.push_back(tmp);
        }
    }
};

#endif // MAJORTOWER_H_INCLUDED
