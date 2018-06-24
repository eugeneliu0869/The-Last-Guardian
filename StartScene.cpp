#include "StartScene.h"

StartScene::StartScene()
{
    background = al_load_bitmap("./image/StartScene/Background.png");

    title_font = al_load_ttf_font("./Li_Xuke.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Li_Xuke.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Li_Xuke.ttf", context_font_size, 0);

    al_reserve_samples(2);

    sample = al_load_sample("./sound/StartScene/SwitchSound.ogg");
    switch_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(switch_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(switch_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/StartScene/EnterSound.ogg");
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

StartScene::~StartScene()
{

}

void
StartScene::SceneInit()
{
    title_x = (window_width - title_width)/2;
    title_y = title_top;

    start_label_x = (window_width - start_label_width)/2;
    start_label_y = title_y + title_height + label_difference * 6;

    select_label_x = (window_width - select_label_width)/2;
    select_label_y = start_label_y + start_label_height + label_difference * 4;

    setting_label_x = (window_width - setting_label_width)/2;
    setting_label_y = select_label_y + select_label_height + label_difference * 4;

    exit_label_x = (window_width - exit_label_width)/2;
    exit_label_y = setting_label_y + setting_label_height + label_difference * 4;

    cout << "Start scene is initialized.\n";
}

void
StartScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "The Last Guardian");

    //al_draw_filled_rectangle(start_label_x, start_label_y, start_label_x + start_label_width, start_label_y + start_label_height, label_color);
    if(start_label_mouse_hover)
    {
        al_draw_filled_rectangle(start_label_x, start_label_y, start_label_x + start_label_width, start_label_y + start_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, start_label_x + start_label_width/2, start_label_y, ALLEGRO_ALIGN_CENTRE, "Start");

    //al_draw_filled_rectangle(select_label_x, select_label_y, select_label_x + select_label_width, select_label_y + select_label_height, label_color);
    if(select_label_mouse_hover)
    {
        al_draw_filled_rectangle(select_label_x, select_label_y, select_label_x + select_label_width, select_label_y + select_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, select_label_x + select_label_width/2, select_label_y, ALLEGRO_ALIGN_CENTRE, "Select");

    //al_draw_filled_rectangle(setting_label_x, setting_label_y, setting_label_x + setting_label_width, setting_label_y + setting_label_height, label_color);
    if(setting_label_mouse_hover)
    {
        al_draw_filled_rectangle(setting_label_x, setting_label_y, setting_label_x + setting_label_width, setting_label_y + setting_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, setting_label_x + setting_label_width/2, setting_label_y, ALLEGRO_ALIGN_CENTRE, "Setting");

    //al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, label_color);
    if(exit_label_mouse_hover)
    {
        al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, exit_label_x + exit_label_width/2, exit_label_y, ALLEGRO_ALIGN_CENTRE, "Exit");

    al_flip_display();
}

int
StartScene::LabelSelected(double pos_x, double pos_y)
{
    if(pos_x >= start_label_x && pos_x <= start_label_x + start_label_width && pos_y >= start_label_y && pos_y <= start_label_y + start_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_BEGIN;
    }
    else if(pos_x >= select_label_x && pos_x <= select_label_x + select_label_width && pos_y >= select_label_y && pos_y <= select_label_y + select_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_SELECT;
    }
    else if(pos_x >= setting_label_x && pos_x <= setting_label_x + setting_label_width && pos_y >= setting_label_y && pos_y <= setting_label_y + setting_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_SETTING;
    }
    else if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_EXIT;
    }
    else
    {
        return GAME_INIT;
    }
}

void
StartScene::LabelMouseHover(double pos_x, double pos_y)
{
    if(pos_x >= start_label_x && pos_x <= start_label_x + start_label_width && pos_y >= start_label_y && pos_y <= start_label_y + start_label_height)
    {
        if(!start_label_mouse_hover)
        {
            al_set_sample_instance_gain(switch_sound, effect_sound_volume);
            al_play_sample_instance(switch_sound);
        }
        start_label_mouse_hover = true;
    }
    else
    {
        start_label_mouse_hover = false;
    }
    if(pos_x >= select_label_x && pos_x <= select_label_x + select_label_width && pos_y >= select_label_y && pos_y <= select_label_y + select_label_height)
    {
        if(!select_label_mouse_hover)
        {
            al_set_sample_instance_gain(switch_sound, effect_sound_volume);
            al_play_sample_instance(switch_sound);
        }
        select_label_mouse_hover = true;
    }
    else
    {
        select_label_mouse_hover = false;
    }
    if(pos_x >= setting_label_x && pos_x <= setting_label_x + setting_label_width && pos_y >= setting_label_y && pos_y <= setting_label_y + setting_label_height)
    {
        if(!setting_label_mouse_hover)
        {
            al_set_sample_instance_gain(switch_sound, effect_sound_volume);
            al_play_sample_instance(switch_sound);
        }
        setting_label_mouse_hover = true;
    }
    else
    {
        setting_label_mouse_hover = false;
    }
    if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        if(!exit_label_mouse_hover)
        {
            al_set_sample_instance_gain(switch_sound, effect_sound_volume);
            al_play_sample_instance(switch_sound);
        }
        exit_label_mouse_hover = true;
    }
    else
    {
        exit_label_mouse_hover = false;
    }
}
