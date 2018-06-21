#ifndef RESULTSCENE_H_INCLUDED
#define RESULTSCENE_H_INCLUDED

#include "Window.h"

#define title_top 50
#define label_difference 10

#define title_font_size 35
#define label_font_size 25
#define context_font_size 20

class ResultScene : public Window
{
public:
    ResultScene();
    ~ResultScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(int, int) override;
};

#endif // RESULTSCENE_H_INCLUDED
