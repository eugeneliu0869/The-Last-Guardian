#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Attack.h"
#include "Minion.h"

class Tower
{
public:
    Tower(int, int);
    ~Tower();

    void Draw();
    void ResetAttackCounter() { attack_counter = 0; }

    bool DetectAttack(Minion*);
    bool TriggerAttack(Minion*);
    void UpdateAttack();

    Circle* getCircle() { return circle; }
    double getCircleX() { return circle->x; }
    double getCircleY() { return circle->y; }
    double getCircleR() { return circle->r; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    char* getName() { return name; }

protected:
    vector<Attack*> attack_set;
    ALLEGRO_BITMAP* attack_image;
    ALLEGRO_BITMAP* image;

    Circle* circle;

    int type = MAJOR_TOWER;
    int width = 40;
    int height = 40;
    char name[30];

    int attack_counter = 0;
    int attack_range = 50;
    int attack_frequency = 50;
    int attack_harm_point = 5;
    int attack_velocity = 5;
};

#endif // TOWER_H_INCLUDED
