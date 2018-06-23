#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

#include "global.h"

#define holy_water_bar_frame_color al_map_rgb(255, 255, 255)
#define score_color al_map_rgb(255, 255, 255)

#define player_holy_water_bar_frame_display_thickness 2

class ScoreBoard
{
public:
    ScoreBoard();
    ~ScoreBoard();

    void Draw();

    void Set_Player_1_HolyWater(int value) { player_1_holy_water = value; }
    void Set_Player_2_HolyWater(int value) { player_2_holy_water = value; }

    int Get_Player_1_HolyWater() { return player_1_holy_water; }
    int Get_Player_2_HolyWater() { return player_2_holy_water; }

    void Change_Player_1_Score(int);
    void Change_Player_2_Score(int);

    void Reset();

private:
    ALLEGRO_BITMAP* background;

    ALLEGRO_FONT* Small_font;
    ALLEGRO_FONT* Medium_font;
    ALLEGRO_FONT* Large_font;
    ALLEGRO_FONT* Giant_font;

    int player_1_holy_water;
    int player_2_holy_water;

    int player_1_score;
    int player_2_score;
};

#endif // SCOREBOARD_H_INCLUDED
