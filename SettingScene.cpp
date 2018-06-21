#include "SettingScene.h"

SettingScene::SettingScene()
{
    background = al_load_bitmap("./image/StartScene/Background.png");

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

SettingScene::~SettingScene()
{

}

void SettingScene::SceneInit()
{
    cout << "Setting scene initializing...\n";

    title_x = (window_width - title_width)/2;
    title_y = title_top;

    exit_label_x = (window_width - exit_label_width)/2;
    exit_label_y = title_y + title_height + label_difference * 19;

    back_sound = new Slider(600, title_y + title_height + label_difference * 5);
    effect_sound = new Slider(600, title_y + title_height + label_difference * 10);

    back_sound->set_label_content("Background Sound");
    back_sound->set_color(al_map_rgb(255, 255, 255));

    effect_sound->set_label_content("Effect Sound");
    effect_sound->set_color(al_map_rgb(255, 255, 255));

    cout << "Start scene drawing...\n";
}

void SettingScene::Draw()
{
    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    //al_draw_filled_rectangle(title_x, title_y, title_x + title_width, title_y + title_height, title_color);
    al_draw_text(title_font, title_text_color, title_x + title_width/2, title_y, ALLEGRO_ALIGN_CENTRE, "Setting");

    back_sound->Draw();

    effect_sound->Draw();

    //al_draw_filled_rectangle(exit_label_x, exit_label_y, exit_label_x + exit_label_width, exit_label_y + exit_label_height, label_color);
    al_draw_text(label_font, label_text_color, exit_label_x + exit_label_width/2, exit_label_y, ALLEGRO_ALIGN_CENTRE, "Exit");

    al_flip_display();
}

int SettingScene::LabelSelected(int pos_x, int pos_y)
{
    if(pos_x >= exit_label_x && pos_x <= exit_label_x + exit_label_width && pos_y >= exit_label_y && pos_y <= exit_label_y + exit_label_height)
    {
        return GAME_BACK;
    }
    else
    {
        return GAME_SETTING;
    }
}
