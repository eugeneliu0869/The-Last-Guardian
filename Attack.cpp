#include "Attack.h"

Attack::Attack(Circle* created_circle, Circle* target_circle, int _harm_point, int _velocity, vector<ALLEGRO_BITMAP*> _attack_image_set)
    : harm_point(_harm_point), attack_velocity(_velocity), attack_image_set(_attack_image_set)
{
    double vector_x = target_circle->x - created_circle->x;
    double vector_y = target_circle->y - created_circle->y;
    double len = sqrt(vector_x * vector_x + vector_y * vector_y);

    // initialize the information of attack
    pos_x = created_circle->x;
    pos_y = created_circle->y;
    circle = new Circle(created_circle->x, created_circle->y, 10);

    direction_x = vector_x / len;
    direction_y = vector_y / len;

    // initialize the effect sound of attack
    sample = al_load_sample("./sound/Attack/AttackSound.ogg");
    attack_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(attack_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(attack_sound, al_get_default_mixer());
    al_set_sample_instance_gain(attack_sound, effect_sound_volume);
    al_play_sample_instance(attack_sound);
}

Attack::~Attack()
{
    al_destroy_sample(sample);
    al_destroy_sample_instance(attack_sound);

    delete circle;
}

void Attack::Draw()
{
    for(auto a:attack_image_set)
    {
        al_draw_bitmap(a, pos_x - circle->r, pos_y - circle->r, 0);
    }


    pos_x += attack_velocity * direction_x;
    pos_y += attack_velocity * direction_y;

    circle->x = pos_x;
    circle->y = pos_y;
}
