#ifndef SELECTSCENE_H_INCLUDED
#define SELECTSCENE_H_INCLUDED

#include "global.h"
#include "Window.h"

#define title_top 50
#define title_down 100
#define label_difference 10

#define title_font_size 40
#define label_font_size 30
#define context_font_size 20

#define map_name_difference_from_image 25
#define map_difference_from_window_side 200
#define map_display_frame_thinkness 3

class SelectScene : public Window
{
public:
    SelectScene();
    ~SelectScene();

    void SceneInit() override;
    void Draw() override;
    void Reset();
    int LabelSelected(double, double) override;
    void LabelMouseHover(double, double) override;

    void map_selected_reset();
    void map_selected(double, double);

private:
    vector<ALLEGRO_BITMAP*> map_set;

    ALLEGRO_SAMPLE_INSTANCE* decision_sound;

    ALLEGRO_COLOR map_selected_color;
    ALLEGRO_COLOR map_unselected_color;

    int title_x, title_y;
    int title_width = 450, title_height = 50;

    int map_width = 104, map_height = 50;

    bool map_1_selected = false;
    int map_1_pos_x, map_1_pos_y;

    bool map_2_selected = false;
    int map_2_pos_x, map_2_pos_y;

    bool map_3_selected = false;
    int map_3_pos_x, map_3_pos_y;

    bool map_4_selected = false;
    int map_4_pos_x, map_4_pos_y;

    bool start_label_mouse_hover = false;
    int start_label_x, start_label_y;
    int start_label_width = 150, start_label_height = 30;

    bool back_label_mouse_hover = false;
    int back_label_x, back_label_y;
    int back_label_width = 100, back_label_height = 30;
};

#endif // SELECTSCENE_H_INCLUDED
