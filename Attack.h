#ifndef ATTACK_H_INCLUDED
#define ATTACK_H_INCLUDED

#include "global.h"
#include "Circle.h"

class Attack
{
public:
    Attack(Circle*, Circle*, int, int, ALLEGRO_BITMAP*);
    ~Attack();

    void Draw();

    Circle* getCircle() { return circle; }
    double getCircleX() { return circle->x; }
    double getCircleY() { return circle->y; }
    double getCircleR() { return circle->r; }
    int getHarmPoint() { return harm_point; }

protected:
    ALLEGRO_BITMAP* attack_image;
    ALLEGRO_SAMPLE* sample;
    ALLEGRO_SAMPLE_INSTANCE* attack_sound;

private:
    Circle* circle;

    int harm_point = 5;
    int attack_velocity = 10;
    double pos_x, pos_y;
    double direction_x, direction_y;
};

#endif // ATTACK_H_INCLUDED
