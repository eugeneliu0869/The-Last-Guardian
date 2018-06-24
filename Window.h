#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "global.h"

class Window
{
public:
   Window();
    ~Window();

    bool get_initial() { return initial; }
    void toggle_initial() { initial = !initial; }

    virtual void SceneInit() = 0;
    virtual void Draw() = 0;
    virtual int LabelSelected(double, double) = 0;
    virtual void LabelMouseHover(double, double) = 0;

protected:
    ALLEGRO_BITMAP *background;

    ALLEGRO_FONT* title_font;
    ALLEGRO_FONT* label_font;
    ALLEGRO_FONT* context_font;

    ALLEGRO_SAMPLE* sample;
    ALLEGRO_SAMPLE_INSTANCE* switch_sound;
    ALLEGRO_SAMPLE_INSTANCE* enter_sound;

    ALLEGRO_COLOR title_color;
    ALLEGRO_COLOR title_text_color;
    ALLEGRO_COLOR label_color;
    ALLEGRO_COLOR label_text_color;
    ALLEGRO_COLOR context_color;
    ALLEGRO_COLOR context_text_color;

    ALLEGRO_COLOR mouse_hover_color;

    bool initial = false;
};

#endif // WINDOW_H_INCLUDED
