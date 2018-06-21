#ifndef SABER_H_INCLUDED
#define SABER_H_INCLUDED

#include "Minion.h"

class Saber : public Minion
{
public:
    Saber(int posx, int posy, int team) : Minion(posx, posy, team)
    {
        this->team = team;
        type = GROUND_UNIT;
        dir_sprite[0] = 3;
        dir_sprite[1] = 3;
        dir_sprite[2] = 3;
        dir_sprite[3] = 3;
        HealthPoint = 20;
        speed = 1;
        cost = 5;
        strcpy(name, "Saber");

        ALLEGRO_BITMAP* test = al_load_bitmap("./image/Minion/Saber/DOWN_2.png");
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
        moveImg.push_back(test);
    }
};

#endif // SABER_H_INCLUDED
