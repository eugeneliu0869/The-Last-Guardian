#ifndef MINION_H_INCLUDED
#define MINION_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "Attack.h"
#include "RangeAttack.h"

#define AIR_UNIT 1
#define GROUND_UNIT 2

#define HEADING_TO_BRIDGE 1
#define PASSING_BRIDGE 2
#define HEADING_TO_TOWER 3

#define UPPER_BRIDGE 1
#define LOWER_BRIDGE 2

#define MELEE 0
#define RANGER 1

enum {LEFT=0, RIGHT, UP, DOWN};

class Minion : public Object
{
public:
    Minion(int, int, int);
    ~Minion();

    bool OnTheBridge(double, double);

    void Draw();
    void find_way();
    void Move();

    void LoadAnimation();
    virtual void LoadAttackAnimation() = 0;

    bool DetectAttack(Minion*);
    bool TriggerAttack(Minion*);
    void UpdateAttack();

    int getHP() { return HealthPoint; }
    int getCost() { return cost; }
    int getTeam() { return team; }
    int getPathStage() { return path_stage; }
    int getIsAttack() { return is_attack; }
    char* getName() { return name; }

    void setSpeed(double rate) { speed *= rate; }
    void setCost(double rate) { cost *= rate; }
    void setTeam(int manipulate) { team = manipulate; }

    void findClosestTower(int, int);

    bool Substract_HP(int);

    int attack_type = -1;

protected:
    int team = red_team;
    int type; // which unit, referring global.h
    int dir_sprite[4]; // numbers of the pictures of each directions
    int HealthPoint = 20;
    int speed = 1;
    int cost = 1;
    char name[20];

    //attack data
    int attack_frequency = 20;
    int attack_counter = 0;
    int attack_harm_point = 5;
    int attack_velocity = 10;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    std::vector<ALLEGRO_BITMAP*> attackImg;

    //set of movement
    std::vector<Minion*> detect_set;
    std::vector<Attack*> attack_set;
    std::vector<RangeAttack*> rangeattack_set;
private:
    // direction and index for "path"
    int cur_direction;
    bool is_attack;

    // animation counter
    int counter;

    int cur_sprite;

    int path_stage = HEADING_TO_BRIDGE;
    double unit_heading_x;
    double unit_heading_y;

    int closest_tower_x;
    int closest_tower_y;

    // feel the need to redesign attack class

} ;

#endif // MINION_H_INCLUDED
