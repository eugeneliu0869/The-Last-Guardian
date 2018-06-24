#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "global.h"
#include "Circle.h"
#include "Object.h"
#include "ScoreBoard.h"

#define hotkey_font_size 12

#define minion_card_width 60
#define minion_card_height 60
#define minion_card_horizontal_difference 10
#define minion_card_top_difference 70
#define minion_card_vertical_difference 40
#define minion_card_display_thickness 2

class Menu : public Object
{
public:
    Menu(int, ScoreBoard*);
    ~Menu();

    void ToggleInitial() { initial = !initial; }

    void Reset();
    void Draw();
    void Initial(int*);

    bool RandomNumExist(int); // show whether the random number has existed

    int getHolyWater() { return holy_water; }
	int getMinionHolyWater(int type) { return needed_holy_water[type]; }

	void GainHolyWater(int);

    bool EnoughHolyWater(int);
    void ChangeHolyWater(int);

    void setMinionRandomSource(int*);

    int MinionSummon(int hotkey);

private:
    ScoreBoard* score_board;

    int team;
    bool initial = false;

	vector<ALLEGRO_BITMAP*> minion_menu_source;

    ALLEGRO_BITMAP* background;

	ALLEGRO_FONT* hotkey_font;

	// UI variables
	ALLEGRO_COLOR menu_context_color;
	ALLEGRO_COLOR card_frame_color;
	ALLEGRO_COLOR enough_holy_water_color;
	//ALLEGRO_COLOR mouse_hover_color;

	int menu_pos_x, menu_pos_y;
	int minion_card_1_pos_x, minion_card_1_pos_y;
	int minion_card_2_pos_x, minion_card_2_pos_y;
	int minion_card_3_pos_x, minion_card_3_pos_y;
	int minion_card_4_pos_x, minion_card_4_pos_y;
	char hotkey_set[4][10];

    int holy_water = 0;
    int needed_holy_water[minion_num] = {-1}; // need to be negative numbers
    int minion_random_source[10] = {-1}; // store minion_random_source which is selected in select scene by the player
    int minion_random_set[4] = {-1}; // store the current minion_random_set that player can summon the minion
};

#endif // MENU_H_INCLUDED

