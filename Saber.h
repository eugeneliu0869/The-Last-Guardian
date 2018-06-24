#ifndef SABER_H_INCLUDED
#define SABER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Minion.h"

class Saber : public Minion
{
public:
    Saber(int, int, int);
    ~Saber();
};

#endif // SABER_H_INCLUDED
