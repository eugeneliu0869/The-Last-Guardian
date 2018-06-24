#include "SelectScene.h"

SelectScene::SelectScene()
{
    char buffer[50];
    ALLEGRO_BITMAP* tmp;

    background = al_load_bitmap("./image/SelectScene/Background.png");

    for(int i = 0; i<map_num; i++)
    {
        sprintf(buffer, "./image/SelectScene/Map_%d.png", i+1);
        tmp = al_load_bitmap(buffer);
        map_set.push_back(tmp);
    }

    al_reserve_samples(3);

    sample = al_load_sample("./sound/SelectScene/SwitchSound.ogg");
    switch_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(switch_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(switch_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/SelectScene/EnterSound.ogg");
    enter_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(enter_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(enter_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/SelectScene/DecisionSound.ogg");
    decision_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(decision_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(decision_sound, al_get_default_mixer());

    title_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", context_font_size, 0);

    title_color = al_map_rgb(0, 0, 0);
    title_text_color = al_map_rgb(255, 129, 0);
    label_color = al_map_rgb(0, 0, 0);
    label_text_color = al_map_rgb(255, 129, 0);
    context_color = al_map_rgb(0, 0, 0);
    context_text_color = al_map_rgb(255, 129, 0);

    mouse_hover_color = al_map_rgba(0, 0, 0, 150);

    map_selected_color = al_map_rgb(255, 165, 0);
    map_unselected_color = al_map_rgb(238, 233, 233);
}

SelectScene::~SelectScene()
{

}

void
SelectScene::SceneInit()
{
    title_x = (window_width - title_width)/2;
    title_y = title_top;

    map_1_pos_x = map_difference_from_window_side;
    map_1_pos_y = title_y + label_difference * 12;

    map_2_pos_x = map_1_pos_x + map_width + (window_width - map_difference_from_window_side * 2 - map_width * map_num) / (map_num - 1);
    map_2_pos_y = map_1_pos_y;

    map_3_pos_x = map_2_pos_x + map_width + (window_width - map_difference_from_window_side * 2 - map_width * map_num) / (map_num - 1);
    map_3_pos_y = map_2_pos_y;

    map_4_pos_x = map_3_pos_x + map_width + (window_width - map_difference_from_window_side * 2 - map_width * map_num) / (map_num - 1);
    map_4_pos_y = map_3_pos_y;

    map_1_selected = true;

    start_label_x = (window_width - start_label_width)/2;
    start_label_y = window_height - title_down;

    back_label_x = window_width - back_label_width - label_difference * 1;
    back_label_y = window_height - back_label_height - label_difference * 1;

    cout << "Select scene is initialized\n";
}

void
SelectScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "Game Select");

    al_draw_bitmap(map_set[0], map_1_pos_x, map_1_pos_y, 0);
    al_draw_text(context_font, context_text_color, map_1_pos_x, map_1_pos_y - map_name_difference_from_image, 0, "Map 1");
    if(map_1_selected)
    {
        al_draw_rectangle(map_1_pos_x, map_1_pos_y, map_1_pos_x + map_width, map_1_pos_y + map_height, map_selected_color, map_display_frame_thinkness);
    }
    else
    {
        al_draw_rectangle(map_1_pos_x, map_1_pos_y, map_1_pos_x + map_width, map_1_pos_y + map_height, map_unselected_color, map_display_frame_thinkness);
    }

    al_draw_bitmap(map_set[1], map_2_pos_x, map_2_pos_y, 0);
    al_draw_text(context_font, context_text_color, map_2_pos_x, map_2_pos_y - map_name_difference_from_image, 0, "Map 2");
    if(map_2_selected)
    {
        al_draw_rectangle(map_2_pos_x, map_2_pos_y, map_2_pos_x + map_width, map_2_pos_y + map_height, map_selected_color, map_display_frame_thinkness);
    }
    else
    {
        al_draw_rectangle(map_2_pos_x, map_2_pos_y, map_2_pos_x + map_width, map_2_pos_y + map_height, map_unselected_color, map_display_frame_thinkness);
    }

    al_draw_bitmap(map_set[2], map_3_pos_x, map_3_pos_y, 0);
    al_draw_text(context_font, context_text_color, map_3_pos_x, map_3_pos_y - map_name_difference_from_image, 0, "Map 3");
    if(map_3_selected)
    {
        al_draw_rectangle(map_3_pos_x, map_3_pos_y, map_3_pos_x + map_width, map_3_pos_y + map_height, map_selected_color, map_display_frame_thinkness);
    }
    else
    {
        al_draw_rectangle(map_3_pos_x, map_3_pos_y, map_3_pos_x + map_width, map_3_pos_y + map_height, map_unselected_color, map_display_frame_thinkness);
    }

    al_draw_bitmap(map_set[3], map_4_pos_x, map_4_pos_y, 0);
    al_draw_text(context_font, context_text_color, map_4_pos_x, map_4_pos_y - map_name_difference_from_image, 0, "Map 4");
    if(map_4_selected)
    {
        al_draw_rectangle(map_4_pos_x, map_4_pos_y, map_4_pos_x + map_width, map_4_pos_y + map_height, map_selected_color, map_display_frame_thinkness);
    }
    else
    {
        al_draw_rectangle(map_4_pos_x, map_4_pos_y, map_4_pos_x + map_width, map_4_pos_y + map_height, map_unselected_color, map_display_frame_thinkness);
    }

    //al_draw_filled_rectangle(start_label_x, start_label_y, start_label_x + start_label_width, start_label_y + start_label_height, label_color);
    if(start_label_mouse_hover)
    {
        al_draw_filled_rectangle(start_label_x, start_label_y, start_label_x + start_label_width, start_label_y + start_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, start_label_x + start_label_width/2, start_label_y, ALLEGRO_ALIGN_CENTRE, "Game Start");

    //al_draw_filled_rectangle(back_label_x, back_label_y, back_label_x + back_label_width, back_label_y + back_label_height, label_color);
    if(back_label_mouse_hover)
    {
        al_draw_filled_rectangle(back_label_x, back_label_y, back_label_x + back_label_width, back_label_y + back_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, back_label_x + back_label_width/2, back_label_y, ALLEGRO_ALIGN_CENTRE, "Back");

    al_flip_display();
}

void
SelectScene::Reset()
{
    map_selected_reset();
    map_1_selected = true;
}

int
SelectScene::LabelSelected(double pos_x, double pos_y)
{
    if(pos_x >= start_label_x && pos_x <= start_label_x + start_label_width && pos_y >= start_label_y && pos_y <= start_label_y + start_label_height)
    {
        map_selected_reset();
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_BEGIN;
    }
    else if(pos_x >= back_label_x && pos_x <= back_label_x + back_label_width && pos_y >= back_label_y && pos_y <= back_label_y + back_label_height)
    {
        map_selected_reset();
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_BACK;
    }
    else
    {
        return GAME_SELECT;
    }
}

void
SelectScene::LabelMouseHover(double pos_x, double pos_y)
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

void
SelectScene::map_selected_reset()
{
    map_1_selected = false;
    map_2_selected = false;
    map_3_selected = false;
    map_4_selected = false;

    game_map = 1;
}

void
SelectScene::map_selected(double pos_x, double pos_y)
{
    if(pos_x >= map_1_pos_x && pos_x <= map_1_pos_x + map_width && pos_y >= map_1_pos_y && pos_y <= map_1_pos_y + map_height)
    {
        map_selected_reset();
        if(al_get_sample_instance_playing(decision_sound))
        {
            al_stop_sample_instance(decision_sound);
        }
        al_set_sample_instance_gain(decision_sound, effect_sound_volume);
        al_play_sample_instance(decision_sound);
        map_1_selected = true;
        game_map = 1;
        cout << "Map 1 selected.\n";
    }
    else if(pos_x >= map_2_pos_x && pos_x <= map_2_pos_x + map_width && pos_y >= map_2_pos_y && pos_y <= map_2_pos_y + map_height)
    {
        map_selected_reset();
        if(al_get_sample_instance_playing(decision_sound))
        {
            al_stop_sample_instance(decision_sound);
        }
        al_set_sample_instance_gain(decision_sound, effect_sound_volume);
        al_play_sample_instance(decision_sound);
        map_2_selected = true;
        game_map = 2;
        cout << "Map 2 selected.\n";
    }
    else if(pos_x >= map_3_pos_x && pos_x <= map_3_pos_x + map_width && pos_y >= map_3_pos_y && pos_y <= map_3_pos_y + map_height)
    {
        map_selected_reset();
        if(al_get_sample_instance_playing(decision_sound))
        {
            al_stop_sample_instance(decision_sound);
        }
        al_set_sample_instance_gain(decision_sound, effect_sound_volume);
        al_play_sample_instance(decision_sound);
        map_3_selected = true;
        game_map = 3;
        cout << "Map 3 selected.\n";
    }
    else if(pos_x >= map_4_pos_x && pos_x <= map_4_pos_x + map_width && pos_y >= map_4_pos_y && pos_y <= map_4_pos_y + map_height)
    {
        map_selected_reset();
        if(al_get_sample_instance_playing(decision_sound))
        {
            al_stop_sample_instance(decision_sound);
        }
        al_set_sample_instance_gain(decision_sound, effect_sound_volume);
        al_play_sample_instance(decision_sound);
        map_4_selected = true;
        game_map = 4;
        cout << "Map 4 selected.\n";
    }
}
