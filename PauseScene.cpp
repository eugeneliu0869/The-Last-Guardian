#include "PauseScene.h"

PauseScene::PauseScene()
{
    background = al_load_bitmap("./image/PauseScene/Background.png");

    title_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", title_font_size, 0);
    label_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", label_font_size, 0);
    context_font = al_load_ttf_font("./Caviar_Dreams_Bold.ttf", context_font_size, 0);

    title_color = al_map_rgb(0, 0, 0);
    title_text_color = al_map_rgb(255, 255, 255);
    label_color = al_map_rgb(0, 0, 0);
    label_text_color = al_map_rgb(255, 255, 255);
    context_color = al_map_rgb(0, 0, 0);
    context_text_color = al_map_rgb(255, 255, 255);
}

PauseScene::~PauseScene()
{

}

void PauseScene::SceneInit()
{
    cout << "Pause scene initializing...\n";

    title_x = (window_width - title_width)/2;
    title_y = title_top;

    continue_label_x = (window_width - continue_label_width)/2;
    continue_label_y = title_y + title_height + label_difference * 7;

    setting_label_x = (window_width - setting_label_width)/2;
    setting_label_y = continue_label_y + continue_label_height + label_difference * 3;

    exit_label_x = (window_width - exit_label_width)/2;
    exit_label_y = setting_label_y + setting_label_height + label_difference * 3;

    back_label_x = window_width - back_label_width - label_difference * 1;
    back_label_y = window_height - back_label_height - label_difference * 1;

    cout << "Pause scene drawing...\n";
}

void PauseScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "Game Pause");

    //al_draw_filled_rectangle(continue_label_x, continue_label_y, continue_label_x + continue_label_width, continue_label_y + continue_label_height, label_color);
    al_draw_text(label_font, label_text_color, continue_label_x + continue_label_width/2, continue_label_y, ALLEGRO_ALIGN_CENTRE, "Continue");

    //al_draw_filled_rectangle(setting_label_x, setting_label_y, setting_label_x + setting_label_width, setting_label_y + setting_label_height, label_color);
    al_draw_text(label_font, label_text_color, setting_label_x + setting_label_width/2, setting_label_y, ALLEGRO_ALIGN_CENTRE, "Setting");

    //al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, label_color);
    al_draw_text(label_font, label_text_color, exit_label_x + exit_label_width/2, exit_label_y, ALLEGRO_ALIGN_CENTRE, "Exit");

    //al_draw_filled_rectangle(back_label_x, back_label_y, back_label_x + back_label_width, back_label_y + back_label_height, label_color);
    al_draw_text(label_font, label_text_color, back_label_x + back_label_width/2, back_label_y, ALLEGRO_ALIGN_CENTRE, "Back");

    al_flip_display();
}

int PauseScene::LabelSelected(int pos_x, int pos_y)
{
    if(pos_x >= continue_label_x && pos_x <= continue_label_x + continue_label_width && pos_y >= continue_label_y && pos_y <= continue_label_y + continue_label_height)
    {
        return GAME_CONTINUE;
    }
    else if(pos_x >= setting_label_x && pos_x <= setting_label_x + setting_label_width && pos_y >= setting_label_y && pos_y <= setting_label_y + setting_label_height)
    {
        return GAME_SETTING;
    }
    else if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        return GAME_EXIT;
    }
    else if(pos_x >= back_label_x && pos_x <= back_label_x + back_label_width && pos_y >= back_label_y && pos_y <= back_label_y + back_label_height)
    {
        return GAME_BACK;
    }
    else
    {
        return GAME_PAUSE;
    }
}
