#include "RangeAttack.h"

RangeAttack::RangeAttack(Circle* _created_circle, Circle* _target_circle,
                         ALLEGRO_BITMAP* _attack_img, ALLEGRO_SAMPLE* _sample,
                         int _harm_point, int _attack_velocity)
{
    this->pos_x = _created_circle->x;
    this->pos_y = _created_circle->y;

    this->attack_circle = new Circle(_created_circle->x, _created_circle->y, 10);
    this->detect_circle = new Circle(_created_circle->x, _created_circle->y, 10);
    this->self_circle = new Circle(_created_circle->x, _created_circle->y, 10);

    double vector_x = _target_circle->x - _created_circle->x;
    double vector_y = _target_circle->y - _created_circle->y;
    double len = sqrt(vector_x * vector_x + vector_y * vector_y);
    this->direction_x = vector_x / len;
    this->direction_y = vector_y / len;

    this->harm_point = _harm_point;
    this->attack_velocity = _attack_velocity;

    this->attack_img = _attack_img;

    this->sample = _sample;
    hit = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hit, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(hit, effect_sound_volume);
    al_attach_sample_instance_to_mixer(hit, al_get_default_mixer());
    al_play_sample_instance(hit);
}

RangeAttack::~RangeAttack()
{
    delete attack_circle;
    delete detect_circle;
    delete self_circle;

    al_destroy_sample(sample);
    al_destroy_sample_instance(hit);
}

void
RangeAttack::Draw()
{
    al_draw_bitmap(attack_img, pos_x - self_circle->r, pos_y - self_circle->r, 0);

    pos_x += attack_velocity * direction_x;
    pos_y += attack_velocity * direction_y;

    attack_circle->x = (double)pos_x;
    attack_circle->y = (double)pos_y;
    detect_circle->x = (double)pos_x;
    detect_circle->y = (double)pos_y;
    self_circle->x = (double)pos_x;
    self_circle->y = (double)pos_y;
}
