#include "Tower.h"

Tower::Tower(int pos_x = 0, int pos_y = 0)
{
    circle = new Circle(pos_x, pos_y, attack_range);
    strcpy(name, "Default");
}

Tower::~Tower()
{
    al_destroy_bitmap(attack_image);
    al_destroy_bitmap(image);

    for(auto i : attack_set)
    {
        delete i;
    }
    attack_set.clear();

    delete circle;
}

void
Tower::Draw()
{
    int draw_x = circle->x - width/2;
    int draw_y = circle->y - height + width/2;

    al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(100, 100, 100, 100));
    al_draw_bitmap(image, draw_x, draw_y, 0);

    attack_counter = (attack_counter + 1 ) % attack_frequency;

    for(auto i : attack_set)
    {
        i->Draw();
    }
}

bool
Tower::DetectAttack(Minion* minion)
{
    bool willAttack = false;
    Attack* attack;

    if(Circle::isOverlap(circle, minion->getAttackCircle() /*minion->getSelfCircle()*/ ))
    {
        if(attack_counter == 0)
        {
            attack = new Attack(circle,
                                minion->getAttackCircle() /*getSelfCircle()*/,
                                attack_harm_point,
                                attack_velocity,
                                attack_image);

            attack_set.push_back(attack);
            willAttack = true;
        }
    }

    return willAttack;
}

bool
Tower::TriggerAttack(Minion* minion)
{
    bool isDestroyed = false;

    for(int i = 0; i<attack_set.size(); i++)
    {
        if(Circle::isOverlap(attack_set[i]->getCircle(), minion->getAttackCircle() /*minion->getSelfCircle()*/ ))
        {
            if(minion->Substract_HP(attack_set[i]->getHarmPoint()))
            {
                isDestroyed = true;
            }

            Attack *attack = attack_set[i];

            attack_set.erase(attack_set.begin() + i);
            i--;
            delete attack;
        }
    }

    return isDestroyed;
}

void
Tower::UpdateAttack()
{
    for(int i = 0; i<attack_set.size(); i++)
    {
        if(!Circle::isOverlap(attack_set[i]->getCircle(), circle))
        {
            Attack *attack = attack_set[i];

            attack_set.erase(attack_set.begin() + i);
            i--;
            delete attack;
        }
    }
}
