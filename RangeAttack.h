#ifndef RANGEATTACK_H_INCLUDED
#define RANGEATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Attack.h"

class RangeAttack : public Attack
{
public:
    RangeAttack(Circle*, Circle*, ALLEGRO_BITMAP*, ALLEGRO_SAMPLE*, int, int);
    ~RangeAttack();

    void Draw() override;
};

#endif // RANGEATTACK_H_INCLUDED
