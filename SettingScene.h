#ifndef SETTINGSCENE_H_INCLUDED
#define SETTINGSCENE_H_INCLUDED

#include "global.h"
#include "Window.h"
#include "Slider.h"

#define title_top 50
#define label_difference 10

#define title_font_size 40
#define label_font_size 30
#define context_font_size 25

class SettingScene : public Window
{
public:
    SettingScene();
    ~SettingScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(double, double) override;
    void LabelMouseHover(double, double) override;

    Slider* background_sound;
    Slider* effect_sound;

private:
    int title_x, title_y;
    int title_width = 450, title_height = 50;

    bool back_label_mouse_hover = false;
    int back_label_x, back_label_y;
    int back_label_width = 100, back_label_height = 30;
};

#endif // SETTINGSCENE_H_INCLUDED
