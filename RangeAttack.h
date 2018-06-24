#ifndef RANGEATTACK_H_INCLUDED
#define RANGEATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Attack.h"

class RangeAttack : public Attack
{
public:
    RangeAttack(Circle* created_circle, Circle* target_circle,
                           ALLEGRO_BITMAP* attack_img, ALLEGRO_SAMPLE* sample,
                           int harm_point, int velocity);
    ~RangeAttack();

    // override virtual function "Object::Draw"
    void Draw() override;

};

#endif // RANGEATTACK_H_INCLUDED
