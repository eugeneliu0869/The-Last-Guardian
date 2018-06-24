#ifndef SABER_H_INCLUDED
#define SABER_H_INCLUDED

#include "Minion.h"

class Saber : public Minion
{
public:
    Saber(int, int, int);
    ~Saber();

    LoadAnimation();
    void LoadAttackAnimation() override;
};

#endif // SABER_H_INCLUDED
