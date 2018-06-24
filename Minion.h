#ifndef MINION_H_INCLUDED
#define MINION_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "RangeAttack.h"
#include "MeleeAttack.h"
#include <string>

#define AIR_UNIT 1
#define GROUND_UNIT 2

#define HEADING_TO_BRIDGE 1
#define PASSING_BRIDGE 2
#define HEADING_TO_TOWER 3

#define UPPER_BRIDGE 1
#define LOWER_BRIDGE 2

#define abs(x) ((x>0) ? x : -x)
enum {LEFT=0, RIGHT, UP, DOWN};

class Minion : public Object
{
public:
    Minion(int, int, int); // circles are defined in subclass
    ~Minion();

    bool OnTheBridge(double, double);

    void Draw();
    void find_way();
    void Move();

    void LoadAnimation();
    virtual void LoadAttackAnimation() = 0;

/// ATTACK RELATED FUNCTION
    bool DetectMinion(Minion*);
    bool TriggerAttackMinion();
    //bool DetectTower(Tower*);
    bool TriggerAttackTower(Tower*);

    void UpdateAttack();
    void resetAttackCounter() { attack_counter = 0; }


    int getHP() { return HealthPoint; }
    int getCost() { return cost; }
    int getTeam() { return team; }
    int getPathStage() { return path_stage; }
    int getIsAttack() { return is_attack; }
    bool getIsRange() { return is_range; }

    void setSpeed(double rate) { speed *= rate; }
    void setCost(double rate) { cost *= rate; }
    void setTeam(int manipulate) { team = manipulate; }

    void findClosestTower(int, int);

    bool Substract_HP(int harm);

protected:
    int team = red_team;
    int type; // which unit, referring global.h
    int dir_sprite[4]; // numbers of the pictures of each directions
    int HealthPoint = 20;
    int speed = 1;
    int cost = 5;
    bool is_range;
    std::string name = "Default";

    int attack_frequency = 20;
    int attack_counter = 0;
    int attack_harm_point = 5;
    int attack_velocity = 10; // if needed
    ALLEGRO_SAMPLE* attack_sound = NULL;
    ALLEGRO_BITMAP* arrow_img = NULL;

    // set of animation images
    std::vector<ALLEGRO_BITMAP*> moveImg;
    std::vector<ALLEGRO_BITMAP*> attackImg; // attack animation
    std::vector<Attack*> attack_set;
    std::vector<Minion*> detect_set;
private:
    // direction and index for "path"
    int cur_direction;
    bool go_attack;
    bool is_attack;


    // animation counter
    int counter;

    int cur_sprite;

    int path_stage;
    double unit_heading_x;
    double unit_heading_y;

    double closest_tower_x;
    double closest_tower_y;


} ;

#endif // MINION_H_INCLUDED
