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
    cost = 5;
    strcpy(name, "Saber");

    LoadAnimation();
    //LoadAttackAnimation();
}

Saber::~Saber()
{

}

void
Saber::LoadAnimation()
{
    ALLEGRO_BITMAP* tmp;
    moveImg.clear();

    // load LEFT move image
    tmp = al_load_bitmap("./image/Minion/Saber/LEFT_1.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/LEFT_2.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/LEFT_3.png");
    moveImg.push_back(tmp);

    // load RIGHT move image
    tmp = al_load_bitmap("./image/Minion/Saber/RIGHT_1.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/RIGHT_2.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/RIGHT_3.png");
    moveImg.push_back(tmp);

    // load UP move image
    tmp = al_load_bitmap("./image/Minion/Saber/UP_1.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/UP_2.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/UP_3.png");
    moveImg.push_back(tmp);

    // load DOWN move image
    tmp = al_load_bitmap("./image/Minion/Saber/DOWN_1.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/DOWN_2.png");
    moveImg.push_back(tmp);
    tmp = al_load_bitmap("./image/Minion/Saber/DOWN_3.png");
    moveImg.push_back(tmp);
}

void
Saber::LoadAttackAnimation()
{

}
