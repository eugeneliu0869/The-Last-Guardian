#ifndef MELEEATTACK_H_INCLUDED
#define MELEEATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Attack.h"

class MeleeAttack : public Attack
{
public:
    MeleeAttack(Circle*, Circle*, ALLEGRO_SAMPLE*, int);
    ~MeleeAttack();

    void Draw() override;
};

#endif // MELEEATTACK_H_INCLUDED
