#include "ResultScene.h"

ResultScene::ResultScene(ScoreBoard* _score_board)
{
    score_board = _score_board;

    background = al_load_bitmap("./image/ResultScene/Background.png");

    title_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Hanyi_Yiyu.ttf", context_font_size, 0);

    al_reserve_samples(2);

    sample = al_load_sample("./sound/ResultScene/SwitchSound.ogg");
    switch_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(switch_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(switch_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/ResultScene/EnterSound.ogg");
    enter_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(enter_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(enter_sound, al_get_default_mixer());

    title_color = al_map_rgb(0, 0, 0);
    title_text_color = al_map_rgb(255, 129, 0);
    label_color = al_map_rgb(0, 0, 0);
    label_text_color = al_map_rgb(255, 129, 0);
    context_color = al_map_rgb(0, 0, 0);
    context_text_color = al_map_rgb(255, 129, 0);

    result_label_color = al_map_rgba(100, 100, 100, 100);
    result_label_frame_color = al_map_rgb(255, 129, 0);

    mouse_hover_color = al_map_rgba(0, 0, 0, 150);
}

ResultScene::~ResultScene()
{

}

void
ResultScene::SceneInit()
{
    title_x = (window_width - title_width)/2;
    title_y = title_top;

    result_label_x = (window_width - result_label_width)/2;
    result_label_y = title_y + title_height + label_difference * 6;

    restart_label_x = (window_width - restart_label_width)/2;
    restart_label_y = result_label_y + result_label_height + label_difference * 6;

    exit_label_x = (window_width - exit_label_width)/2;
    exit_label_y = restart_label_y + restart_label_height + label_difference * 5;

    cout << "Result scene is initialized\n";
}

void
ResultScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "Game End");

    al_draw_filled_rectangle(result_label_x, result_label_y, result_label_x + result_label_width, result_label_y + result_label_height, result_label_color);
    al_draw_rectangle(result_label_x, result_label_y, result_label_x + result_label_width, result_label_y + result_label_height, result_label_frame_color, result_display_thinkness);
    if(score_board->Get_Player_1_Score() > score_board->Get_Player_2_Score())
    {
        al_draw_text(label_font, player_1_color, result_label_x + result_label_width/2, result_label_y + 20, ALLEGRO_ALIGN_CENTRE, "Player 1 wins !");
    }
    else if(score_board->Get_Player_1_Score() < score_board->Get_Player_2_Score())
    {
        al_draw_text(label_font, player_2_color, result_label_x + result_label_width/2, result_label_y + 20, ALLEGRO_ALIGN_CENTRE, "Player 2 wins !");
    }
    else
    {
        al_draw_text(label_font, label_text_color, result_label_x + result_label_width/2, result_label_y + 20, ALLEGRO_ALIGN_CENTRE, "Draw !");
    }

    char buffer[50];
    sprintf(buffer, "%d", score_board->Get_Player_1_Score());
    al_draw_text(label_font, player_1_color, result_label_x + result_label_width/2 - 35, result_label_y + 80, ALLEGRO_ALIGN_CENTRE, buffer);
    al_draw_text(label_font, label_text_color, result_label_x + result_label_width/2, result_label_y + 80, ALLEGRO_ALIGN_CENTRE, ":");
    sprintf(buffer, "%d", score_board->Get_Player_2_Score());
    al_draw_text(label_font, player_2_color, result_label_x + result_label_width/2 + 35, result_label_y + 80, ALLEGRO_ALIGN_CENTRE, buffer);

    //al_draw_filled_rectangle(restart_label_x, restart_label_y, restart_label_x + restart_label_width, restart_label_y + restart_label_height, label_color);
    if(restart_label_mouse_hover)
    {
        al_draw_filled_rectangle(restart_label_x, restart_label_y, restart_label_x + restart_label_width, restart_label_y + restart_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, restart_label_x + restart_label_width/2, restart_label_y, ALLEGRO_ALIGN_CENTRE, "Restart");

    //al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, label_color);
    if(exit_label_mouse_hover)
    {
        al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, mouse_hover_color);
    }
    al_draw_text(label_font, label_text_color, exit_label_x + exit_label_width/2, exit_label_y, ALLEGRO_ALIGN_CENTRE, "Exit");

    al_flip_display();
}

int
ResultScene::LabelSelected(double pos_x, double pos_y)
{
    if(pos_x >= restart_label_x && pos_x <= restart_label_x + restart_label_width && pos_y >= restart_label_y && pos_y <= restart_label_y + restart_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_INIT;
    }
    else if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        al_set_sample_instance_gain(enter_sound, effect_sound_volume);
        al_play_sample_instance(enter_sound);
        return GAME_EXIT;
    }
    else
    {
        return GAME_RESULT;
    }
}

void
ResultScene::LabelMouseHover(double pos_x, double pos_y)
{
    if(pos_x >= restart_label_x && pos_x <= restart_label_x + restart_label_width && pos_y >= restart_label_y && pos_y <= restart_label_y + restart_label_height)
    {
        if(!restart_label_mouse_hover)
        {
            al_set_sample_instance_gain(switch_sound, effect_sound_volume);
            al_play_sample_instance(switch_sound);
        }
        restart_label_mouse_hover = true;
    }
    else
    {
        restart_label_mouse_hover = false;
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
