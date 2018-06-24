#include "MeleeAttack.h"

MeleeAttack::MeleeAttack(Circle* _attack_circle, Circle* target_circle , ALLEGRO_SAMPLE* sample, int harm_point);
{
    this->pos_x = _attack_circle->x;
    this->pos_y = _attack_circle->y;
    this->self_circle = new Circle(_attack_circle);

    double vector_x = target_circle->x - created_circle->x;
    double vector_y = target_circle->y - created_circle->y;
    double len = sqrt(vector_x * vector_x + vector_y * vector_y);
    this->direction_x = vector_x / len;
    this->direction_y = vector_y / len;

    this->harm_point = harm_point;

    this->sample = sample;
    hit = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hit, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(hit, al_get_default_mixer());
    al_set_sample_instance_gain(hit, volume);
    al_play_sample_instance(hit);
}

MeleeAttack::~MeleeAttack()
{
    delete self_circle;
    if (sample)
        al_destroy_sample(sample);
    if (arrow)
        al_destroy_sample_instance(arrow);
}

void
MeleeAttack::Draw()
{

}
/// 砍的動畫打的時間
