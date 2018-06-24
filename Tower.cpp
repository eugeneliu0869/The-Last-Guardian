#include "Tower.h"
#include "Minion.h"

Tower::Tower(int pos_x = 0, int pos_y = 0)
{
    attack_circle = new Circle(pos_x, pos_y, attack_range);
    detect_circle = new Circle(pos_x, pos_y, detect_range);
    self_circle = new Circle(pos_x, pos_y, self_range);
    strcpy(name, "Default");
}

Tower::~Tower()
{
    for(auto i : image_set)
    {
        al_destroy_bitmap(i);
    }
    image_set.clear();
    al_destroy_bitmap(attack_image);

    for(auto i : attack_set)
    {
        delete i;
    }
    attack_set.clear();

    delete attack_circle;
    delete detect_circle;
    delete self_circle;
}

void
Tower::Draw()
{
    double draw_x = self_circle->x - width/2;
    double draw_y = self_circle->y - height + width;

    al_draw_filled_circle(self_circle->x, self_circle->y, self_circle->r, al_map_rgba(100, 100, 100, 100));
    al_draw_bitmap(image_set[cur_sprite], draw_x, draw_y, 0);

    attack_counter = (attack_counter + 1 ) % attack_frequency;

    animation_counter = (animation_counter + 1) % animation_frequency;
    if(animation_counter == 0)
    {
        cur_sprite = (cur_sprite + 1) % sprite_num;
    }

    for(auto i : attack_set)
    {
        i->Draw();
    }
}

bool
Tower::DetectAttack(Minion* minion)
{
    bool willAttack = false;
    TowerAttack* attack;

    if(Circle::isOverlap(detect_circle, minion->getSelfCircle()))
    {
        if(attack_counter == 0)
        {
            attack = new TowerAttack(detect_circle,
                                     minion->getSelfCircle(),
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
        if(Circle::isOverlap(attack_set[i]->getCircle(), minion->getSelfCircle()))
        {
            if(minion->Substract_HP(attack_set[i]->getHarmPoint()))
            {
                isDestroyed = true;
            }

            TowerAttack* attack = attack_set[i];

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
        if(!Circle::isOverlap(attack_set[i]->getCircle(), attack_circle))
        {
            TowerAttack* attack = attack_set[i];

            attack_set.erase(attack_set.begin() + i);
            i--;
            delete attack;
        }
    }
}

bool Tower::Substract_HP(int harm)
{
    HP -= harm;

    return (HP <= 0);
}
