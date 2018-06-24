#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(Circle* _created_circle, Circle* _target_circle,
                         ALLEGRO_SAMPLE* _sample, int _harm_point)
{
    this->pos_x = _created_circle->x;
    this->pos_y = _created_circle->y;

    this->attack_circle = new Circle(_created_circle->x, _created_circle->y, _created_circle->r);
    this->detect_circle = new Circle(_created_circle->x, _created_circle->y, _created_circle->r);
    this->self_circle = new Circle(_created_circle->x, _created_circle->y, _created_circle->r);

    double vector_x = _target_circle->x - _created_circle->x;
    double vector_y = _target_circle->y - _created_circle->y;
    double len = sqrt(vector_x * vector_x + vector_y * vector_y);
    this->direction_x = vector_x / len;
    this->direction_y = vector_y / len;

    this->harm_point = _harm_point;

    this->sample = _sample;
    hit = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hit, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(hit, effect_sound_volume);
    al_attach_sample_instance_to_mixer(hit, al_get_default_mixer());
    al_play_sample_instance(hit);
}

MeleeAttack::~MeleeAttack()
{
    delete attack_circle;
    delete detect_circle;
    delete self_circle;

    al_destroy_sample(sample);
    al_destroy_sample_instance(hit);
}

void
MeleeAttack::Draw()
{

}
