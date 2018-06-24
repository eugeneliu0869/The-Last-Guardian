#include "Saber.h"

Saber::Saber(int posx, int posy, int team) : Minion(posx, posy, team)
{
    this->team = team;
    type = GROUND_UNIT;
    dir_sprite[0] = 3; // LEFT dir_sprite
    dir_sprite[1] = 3; // RIGHT dir_sprite
    dir_sprite[2] = 3; // UP dir_sprite
    dir_sprite[3] = 3; // DOWN dir_sprite
    HealthPoint = 20;
    speed = 1;
    cost = 1;
    strcpy(name, "Saber");

    Minion::LoadAnimation();
    //LoadAttackAnimation();
}

Saber::~Saber()
{

}

void
Saber::LoadAttackAnimation()
{

}
