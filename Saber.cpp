#include "Saber.h"

Saber::Saber(int pos_x, int pos_y, int _team) : Minion(pos_x, pos_y, _team)
{
    team = _team;
    HP = 20;
    speed = 1;
    cost = 1;
    strcpy(name, "Saber");

    type = GROUND_UNIT;

    // LEFT -> RIGHT -> UP -> DOWN
    dir_sprite[0] = 3;
    dir_sprite[1] = 3;
    dir_sprite[2] = 0;
    dir_sprite[3] = 0;

    attack_dir_sprite[0] = 3;
    attack_dir_sprite[1] = 3;
    attack_dir_sprite[2] = 0;
    attack_dir_sprite[3] = 0;

    attack_frequency = 20;
    attack_harm_point = 5;
    attack_velocity = 10;

    Minion::LoadAnimation();
}

Saber::~Saber()
{

}
