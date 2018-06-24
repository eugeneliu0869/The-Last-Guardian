#ifndef RESULTSCENE_H_INCLUDED
#define RESULTSCENE_H_INCLUDED

#include "Window.h"
#include "ScoreBoard.h"

#define title_top 50
#define label_difference 10

#define title_font_size 40
#define label_font_size 30
#define context_font_size 25

#define result_display_thinkness 3

class ResultScene : public Window
{
public:
    ResultScene(ScoreBoard*);
    ~ResultScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(double, double) override;
    void LabelMouseHover(double, double) override;

private:
    ScoreBoard* score_board;

    ALLEGRO_COLOR result_label_color;
    ALLEGRO_COLOR result_label_frame_color;

    int title_x, title_y;
    int title_width = 450, title_height = 40;

    int result_label_x, result_label_y;
    int result_label_width = 300, result_label_height = 140;

    bool restart_label_mouse_hover = false;
    int restart_label_x, restart_label_y;
    int restart_label_width = 100, restart_label_height = 30;

    bool exit_label_mouse_hover = false;
    int exit_label_x, exit_label_y;
    int exit_label_width = 100, exit_label_height = 30;
};

#endif // RESULTSCENE_H_INCLUDED
