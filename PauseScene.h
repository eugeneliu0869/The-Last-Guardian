#ifndef PAUSESCENE_H_INCLUDED
#define PAUSESCENE_H_INCLUDED

#include "Window.h"

#define title_top 50
#define label_difference 10

#define title_font_size 35
#define label_font_size 25
#define context_font_size 20

class PauseScene : public Window
{
public:
    PauseScene();
    ~PauseScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(int, int) override;

private:
    int title_x, title_y;
    int title_width = 200, title_height = 40;
    int continue_label_x, continue_label_y;
    int continue_label_width = 100, continue_label_height = 30;
    int setting_label_x, setting_label_y;
    int setting_label_width = 100, setting_label_height = 30;
    int exit_label_x, exit_label_y;
    int exit_label_width = 100, exit_label_height = 30;
    int back_label_x, back_label_y;
    int back_label_width = 100, back_label_height = 30;
};

#endif // PAUSESCENE_H_INCLUDED
