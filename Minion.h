#ifndef MINION_H_INCLUDED
#define MINION_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Attack.h"
#include "RangeAttack.h"
#include "MeleeAttack.h"

#define AIR_UNIT 1
#define GROUND_UNIT 2

#define HEADING_TO_BRIDGE 1
#define PASSING_BRIDGE 2
#define HEADING_TO_TOWER 3

#define UPPER_BRIDGE 1
#define LOWER_BRIDGE 2

enum {LEFT = 0, RIGHT, UP, DOWN};

class Tower;

class Minion : public Object
{
public:
    Minion(int, int, int); // circles are defined in subclass
    ~Minion();

    bool Substract_HP(int);
    bool OnTheBridge(double, double);

    void Draw() override;
    void find_way();
    void Move();

    void LoadAnimation();

    void findClosestTower(double, double);

    bool DetectMinion(Minion*);
    bool TriggerAttackMinion(Minion*);

    //bool DetectTower(Tower*);
    bool TriggerAttackTower(Tower*);

    void UpdateAttack();
    void resetAttackCounter() { attack_counter = 0; }

    int getTeam() { return team; }
    int getHP() { return HP; }
    int getSpeed() { return speed; }
    int getCost() { return cost; }
    char* getName() { return name; }

    bool getIsAttack() { return is_attack; }
    bool getIsRange() { return is_range; }
    int getPathStage() { return path_stage; }

protected:
    int team = red_team;
    int HP = 20;
    int speed = 1;
    int cost = 1;
    char name[50];

    int type;
    int dir_sprite[4]; // numbers of the moving pictures of each directions
    int attack_dir_sprite[4]; // numbers of the attacking pictures of each directions

    int attack_frequency = 20;
    int attack_counter = 0;
    int attack_harm_point = 5;
    int attack_velocity = 10; // if needed

    ALLEGRO_SAMPLE* attack_sound = NULL;
    ALLEGRO_BITMAP* arrow_img = NULL;

    // set of animation images
    vector<ALLEGRO_BITMAP*> moveImg;
    vector<ALLEGRO_BITMAP*> attackImg; // attack animation
    vector<Attack*> attack_set;
    vector<Minion*> detect_set;

private:
    bool go_attack;
    bool is_attack;
    bool is_range;

    int counter;
    int cur_sprite;
    int cur_direction;
    int path_stage;

    double unit_heading_x;
    double unit_heading_y;

    double closest_tower_x;
    double closest_tower_y;
} ;

#endif // MINION_H_INCLUDED
