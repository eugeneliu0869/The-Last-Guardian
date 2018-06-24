#include "RangeAttack.h"

RangeAttack::RangeAttack(Circle* created_circle, Circle* target_circle,
                           ALLEGRO_BITMAP* attack_img, ALLEGRO_SAMPLE* sample,
                           int harm_point, int velocity)
{
    double vector_x = target_circle->x - created_circle->x;
    double vector_y = target_circle->y - created_circle->y;
    double len = sqrt(vector_x * vector_x + vector_y * vector_y);

    this->pos_x = created_circle->x;
    this->pos_y = created_circle->y;
    this->self_circle = new Circle(created_circle->x, created_circle->y, 10);

    this->direction_x = vector_x / len;
    this->direction_y = vector_y / len;

    this->attack_velocity = velocity;
    this->harm_point = harm_point;

    this->attack_img = attack_img;
    this->sample = sample;
    arrow = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(arrow, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(arrow, al_get_default_mixer());
    al_set_sample_instance_gain(arrow, volume);
    al_play_sample_instance(arrow);
}

RangeAttack::~RangeAttack()
{
    delete self_circle;
    al_destroy_sample_instance(arrow);
    al_destroy_sample(sample);
}

void
RangeAttack::Draw()
{
    al_draw_bitmap(attack_img, pos_x - self_circle->r, pos_y - self_circle->r, 0);
    pos_x += attack_velocity * direction_x;
    pos_y += attack_velocity * direction_y;

    self_circle->x = (int)pos_x;
    self_circle->y = (int)pos_y;

    //al_draw_filled_circle(pos_x, pos_y, circle->r, al_map_rgba(196, 79, 79, 200));
}

