#ifndef EXITSCENE_H_INCLUDED
#define EXITSCENE_H_INCLUDED

#include "global.h"
#include "Window.h"

#define title_top 50
#define label_difference 10

#define title_font_size 35
#define label_font_size 25
#define context_font_size 20

class ExitScene : public Window
{
public:
    ExitScene();
    ~ExitScene();

    void SceneInit() override;
    void Draw() override;
    int LabelSelected(int, int) override;
};

#endif // EXITSCENE_H_INCLUDED
