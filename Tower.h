#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "TowerAttack.h"

class Minion;

class Tower : public Object
{
public:
    Tower(int, int);
    ~Tower();

    void Draw() override;
    void ResetAttackCounter() { attack_counter = 0; }

    bool DetectAttack(Minion*);
    bool TriggerAttack(Minion*);
    void UpdateAttack();

    bool Substract_HP(int);

    int getWidth() { return width; }
    int getHeight() { return height; }
    int getHP() { return HP; }
    char* getName() { return name; }

protected:
    vector<ALLEGRO_BITMAP*> image_set;
    ALLEGRO_BITMAP* attack_image;

    vector<TowerAttack*> attack_set;

    int sprite_num = 14;
    int cur_sprite = 0;
    int animation_counter = 0;
    int animation_frequency = 2;

    int type = MAJOR_TOWER;
    int width = 40;
    int height = 40;
    char name[30];

    int attack_range = 50;
    int detect_range = 50;
    int self_range = 10;

    int HP = 50;
    int attack_counter = 0;
    int attack_frequency = 50;
    int attack_harm_point = 5;
    int attack_velocity = 5;
};

#endif // TOWER_H_INCLUDED
