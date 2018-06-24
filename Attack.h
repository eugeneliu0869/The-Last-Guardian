#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"

class Attack : public Object
{
public:
    Attack() { }
    ~Attack() { }

    virtual void Draw() = 0;
    int getHarmPoint() { return harm_point; }

protected:
    ALLEGRO_BITMAP* attack_img;
    ALLEGRO_SAMPLE* sample;
    ALLEGRO_SAMPLE_INSTANCE* hit = NULL;

    int attack_velocity = 0;
    int harm_point = 0;
    double pos_x, pos_y;
    double direction_x, direction_y;
};

#endif // ATTACK_H_INCLUDED
