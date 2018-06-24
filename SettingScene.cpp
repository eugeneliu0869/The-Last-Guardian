#include "SettingScene.h"

SettingScene::SettingScene()
{
    background = al_load_bitmap("./image/SettingScene/Background.png");

    title_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", context_font_size, 0);

    al_reserve_samples(2);

    sample = al_load_sample("./sound/SettingScene/SwitchSound.ogg");
    switch_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(switch_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(switch_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/SettingScene/EnterSound.ogg");
    enter_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(enter_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(enter_sound, al_get_default_mixer());

    title_color = al_map_rgb(0, 0, 0);
    title_text_color = al_map_rgb(255, 129, 0);
    label_color = al_map_rgb(0, 0, 0);
    label_text_color = al_map_rgb(255, 129, 0);
    context_color = al_map_rgb(0, 0, 0);
    context_text_color = al_map_rgb(255, 129, 0);

    mouse_hover_color = al_map_rgba(0, 0, 0, 150);
}

SettingScene::~SettingScene()
{

}

void
SettingScene::SceneInit()
{
    title_x = (window_width - title_width)/2;
    title_y = title_top;

    back_label_x = window_width - back_label_width - label_difference * 1;
    back_label_y = window_height - back_label_height - label_difference * 1;

    background_sound = new Slider(500, title_y + title_height + label_difference * 8);
    effect_sound = new Slider(500, title_y + title_height + label_difference * 20);

    background_sound->set_label_content("Background Sound");
    background_sound->set_color(al_map_rgb(255, 129, 0));

    effect_sound->set_label_content("Effect Sound");
    effect_sound->set_color(al_map_rgb(255, 129, 0));

    cout << "Setting scene is initialized.\n";
}

void
SettingScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "Setting");

    background_sound->Draw();
    effect_sound->Draw();

    //al_draw_filled_rectangle(back_label_x, back_label_y, back_label_x + back_label_width, back_label_y + back_label_height, label_color);
    if(back_label_mouse_hover)
    {
        al_draw_filled_rectangle(back_label_x, back_label_y, back_label_x + back_label_width, back_label_y + back_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, back_label_x + back_label_width/2, back_label_y, ALLEGRO_ALIGN_CENTRE, "Back");

    al_flip_display();
}

int
SettingScene::LabelSelected(double pos_x, double pos_y)
{
    if(pos_x >= back_label_x && pos_x <= back_label_x + back_label_width && pos_y >= back_label_y && pos_y <= back_label_y + back_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_BACK;
    }
    else
    {
        return GAME_SETTING;
    }
}

void
SettingScene::LabelMouseHover(double pos_x, double pos_y)
{
    if(pos_x >= back_label_x && pos_x <= back_label_x + back_label_width && pos_y >= back_label_y && pos_y <= back_label_y + back_label_height)
    {
        if(!back_label_mouse_hover)
        {
            al_set_sample_instance_gain(switch_sound, effect_sound_volume);
            al_play_sample_instance(switch_sound);
        }
        back_label_mouse_hover = true;
    }
    else
    {
        back_label_mouse_hover = false;
    }
}
