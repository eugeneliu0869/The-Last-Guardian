#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"

class Attack : public Object
{
public:
    virtual Attack() = 0;
    virtual ~Attack() = 0;

    virtual Draw() = 0;
    int getHarmPoint() { return harm_point; }
    void setVolume() { return volume; }

protected:

    float volume = 1.0;
    ALLEGRO_BITMAP *attack_img;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *arrow = NULL;

    int attack_velocity = 8;
    int harm_point = 5;
    double pos_x, pos_y;
    double direction_x, direction_y;
};


#endif // ATTACK_H_INCLUDED
