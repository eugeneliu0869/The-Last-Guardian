#ifndef MELEEATTACK_H_INCLUDED
#define MELEEATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Attack.h"

class MeleeAttack : public Attack
{
public:
    MeleeAttack(Circle* _attack_circle, Circle* target_circle, ALLEGRO_SAMPLE* sample, int harm_point);
    ~MeleeAttack();

    void Draw() override;

};


#endif // MELEEATTACK_H_INCLUDED
