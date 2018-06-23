#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
    background = al_load_bitmap("./image/ScoreBoard/Background.png");

    Small_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0);
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0);
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0);
    Giant_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",50,0);

    player_1_holy_water = 0;
    player_2_holy_water = 0;

    player_1_score = 0;
    player_2_score = 0;
}

ScoreBoard::~ScoreBoard()
{
    al_destroy_bitmap(background);

    al_destroy_font(Small_font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    al_destroy_font(Giant_font);
}

void ScoreBoard::Draw()
{
    al_draw_bitmap(background, 0, 0, 0);

    // draw players' holy water bar
    char player_1_holy_water_display[5];
    sprintf(player_1_holy_water_display, "%d", player_1_holy_water);
    al_draw_text(Medium_font, player_1_color, 20, 20, 0, "Player 1's Holy Water Bar");
    al_draw_text(Medium_font, player_1_color, 20 + 300 + 30, 60 - 5, ALLEGRO_ALIGN_CENTER, player_1_holy_water_display);
    al_draw_filled_rectangle(20, 60, 20 + 30 * player_1_holy_water, 80, player_1_color);
    for(int i = 0; i <= max_holy_water; i++)
    {
        al_draw_rectangle(20, 60, 20 + 30 * i, 80,
                          holy_water_bar_frame_color, player_holy_water_bar_frame_display_thickness);
    }

    char player_2_holy_water_display[5];
    sprintf(player_2_holy_water_display, "%d", player_2_holy_water);
    al_draw_text(Medium_font, player_2_color, window_width - 20 - 300, 20, 0, "Player 2's Holy Water Bar");
    al_draw_text(Medium_font, player_2_color,  window_width - 20 - 300 - 30, 60 - 5, ALLEGRO_ALIGN_CENTER, player_2_holy_water_display);
    al_draw_filled_rectangle(window_width - 20 - 300, 60, window_width - 20 - 300 + 30 * player_2_holy_water, 80, player_2_color);
    for(int i = 0; i <= max_holy_water; i++)
    {
        al_draw_rectangle(window_width - 20 - 300, 60, window_width - 20 - 300 + 30 * i, 80,
                          holy_water_bar_frame_color, player_holy_water_bar_frame_display_thickness);
    }

    // draw score
    char player_1_score_display[5], player_2_score_display[5];
    sprintf(player_1_score_display, "%d", player_1_score);
    sprintf(player_2_score_display, "%d", player_2_score);

    al_draw_text(Giant_font, score_color, window_width/2 - 100, scoreboard_height/2 - 25, ALLEGRO_ALIGN_CENTER, player_1_score_display);
    al_draw_text(Giant_font, score_color, window_width/2, scoreboard_height/2 - 25, ALLEGRO_ALIGN_CENTER, ":");
    al_draw_text(Giant_font, score_color, window_width/2 + 100, scoreboard_height/2 - 25, ALLEGRO_ALIGN_CENTER, player_2_score_display);
}

void ScoreBoard::Change_Player_1_Score(int change)
{

}

void ScoreBoard::Change_Player_2_Score(int change)
{

}

void ScoreBoard::Reset()
{
    player_1_holy_water = 0;
    player_2_holy_water = 0;

    player_1_score = 0;
    player_2_score = 0;
}
