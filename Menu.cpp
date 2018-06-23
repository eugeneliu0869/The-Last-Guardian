#include "Menu.h"

Menu::Menu(int _team)
{
    team = _team;
	holy_water = 0;

    background = al_load_bitmap("./image/Menu/Background.png"); // load background

    hotkey_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf", hotkey_font_size, 0); // load hotkey font

    // UI variables initialization
    if(team == red_team)
    {
    	menu_context_color = player_1_color;
    	card_frame_color = player_1_color;

		menu_pos_x = 0;
		menu_pos_y = scoreboard_height;
		minion_card_1_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_1_pos_y = menu_pos_y + minion_card_top_difference;
		minion_card_2_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_2_pos_y = minion_card_1_pos_y + minion_card_height + minion_card_vertical_difference;
		minion_card_3_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_3_pos_y = minion_card_2_pos_y + minion_card_height + minion_card_vertical_difference;
		minion_card_4_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_4_pos_y = minion_card_3_pos_y + minion_card_height + minion_card_vertical_difference;

		strcpy(hotkey_set[0], "B");
		strcpy(hotkey_set[1], "N");
		strcpy(hotkey_set[2], "M");
		strcpy(hotkey_set[3], "G");
    }
	else if(team == blue_team)
	{
		menu_context_color = player_2_color;
		card_frame_color = player_2_color;

		menu_pos_x = window_width - menu_width;
		menu_pos_y = scoreboard_height;
		minion_card_1_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_1_pos_y = menu_pos_y + minion_card_top_difference;
		minion_card_2_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_2_pos_y = minion_card_1_pos_y + minion_card_height + minion_card_vertical_difference;
		minion_card_3_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_3_pos_y = minion_card_2_pos_y + minion_card_height + minion_card_vertical_difference;
		minion_card_4_pos_x = menu_pos_x + minion_card_horizontal_difference;
		minion_card_4_pos_y = minion_card_3_pos_y + minion_card_height + minion_card_vertical_difference;

		strcpy(hotkey_set[0], "1");
		strcpy(hotkey_set[1], "2");
		strcpy(hotkey_set[2], "3");
		strcpy(hotkey_set[3], "4");
	}

	enough_holy_water_color = al_map_rgba(100, 100, 100, 100);
}

Menu::~Menu()
{
	Reset();

	al_destroy_bitmap(background);

	al_destroy_font(hotkey_font);
}

void Menu::Reset()
{
	holy_water = 0;

	// clean all the minion_menu bitmaps
	for(vector<ALLEGRO_BITMAP*>::iterator it = minion_menu_source.begin(); it != minion_menu_source.end(); it++)
	{
		al_destroy_bitmap((*it));
	}
	minion_menu_source.clear();

	// clean minion_random_source
	for(int i = 0; i<10; i++)
	{
		minion_random_source[i] = -1;
	}

	// clean minion_random_set
	for(int i = 0; i<4; i++)
	{
		minion_random_set[i] = -1;
	}

	ToggleInitial();
}

void Menu::Draw()
{
	al_draw_bitmap(background, menu_pos_x, menu_pos_y, 0);

	// draw essential UI frame
	al_draw_text(hotkey_font, menu_context_color, minion_card_1_pos_x, minion_card_1_pos_y - 15, 0, hotkey_set[0]);
    al_draw_rectangle(minion_card_1_pos_x, minion_card_1_pos_y,
                      minion_card_1_pos_x + minion_card_width, minion_card_1_pos_y + minion_card_height,
                      card_frame_color, minion_card_display_thickness);
    al_draw_text(hotkey_font, menu_context_color, minion_card_2_pos_x, minion_card_2_pos_y - 15, 0, hotkey_set[1]);
    al_draw_rectangle(minion_card_2_pos_x, minion_card_2_pos_y,
                      minion_card_2_pos_x + minion_card_width, minion_card_2_pos_y + minion_card_height,
                      card_frame_color, minion_card_display_thickness);
    al_draw_text(hotkey_font, menu_context_color, minion_card_3_pos_x, minion_card_3_pos_y - 15, 0, hotkey_set[2]);
    al_draw_rectangle(minion_card_3_pos_x, minion_card_3_pos_y,
                      minion_card_3_pos_x + minion_card_width, minion_card_3_pos_y + minion_card_height,
                      card_frame_color, minion_card_display_thickness);
    al_draw_text(hotkey_font, menu_context_color, minion_card_4_pos_x, minion_card_4_pos_y - 15, 0, hotkey_set[3]);
    al_draw_rectangle(minion_card_4_pos_x, minion_card_4_pos_y,
                      minion_card_4_pos_x + minion_card_width, minion_card_4_pos_y + minion_card_height,
                      card_frame_color, minion_card_display_thickness);

    // draw minion bitmaps
    al_draw_bitmap(minion_menu_source[minion_random_set[0]], minion_card_1_pos_x, minion_card_1_pos_y, 0);
    al_draw_bitmap(minion_menu_source[minion_random_set[1]], minion_card_2_pos_x, minion_card_2_pos_y, 0);
    al_draw_bitmap(minion_menu_source[minion_random_set[2]], minion_card_3_pos_x, minion_card_3_pos_y, 0);
    al_draw_bitmap(minion_menu_source[minion_random_set[3]], minion_card_4_pos_x, minion_card_4_pos_y, 0);

    // show whether there is enough holy water
    if(!EnoughHolyWater(minion_random_set[0]))
    {
        al_draw_filled_rectangle(minion_card_1_pos_x, minion_card_1_pos_y,
                                 minion_card_1_pos_x + minion_card_width, minion_card_1_pos_y + minion_card_height,
                                 enough_holy_water_color);
    }
    if(!EnoughHolyWater(minion_random_set[1]))
    {
        al_draw_filled_rectangle(minion_card_2_pos_x, minion_card_2_pos_y,
                                 minion_card_2_pos_x + minion_card_width, minion_card_2_pos_y + minion_card_height,
                                 enough_holy_water_color);
    }
    if(!EnoughHolyWater(minion_random_set[2]))
    {
        al_draw_filled_rectangle(minion_card_3_pos_x, minion_card_3_pos_y,
                                 minion_card_3_pos_x + minion_card_width, minion_card_3_pos_y + minion_card_height,
                                 enough_holy_water_color);
    }
    if(!EnoughHolyWater(minion_random_set[3]))
    {
        al_draw_filled_rectangle(minion_card_4_pos_x, minion_card_4_pos_y,
                                 minion_card_4_pos_x + minion_card_width, minion_card_4_pos_y + minion_card_height,
                                 enough_holy_water_color);
    }
}

void Menu::Initial(int _minion_random_source[])
{
	char minion_name_set[10][30];

	setMinionRandomSource(_minion_random_source);

	// load the minion_menu_source
	for(int i = 0;i<10;i++)
	{
		sprintf(minion_name_set[i], "./image/Menu/%s_menu.png", ArmyClass[minion_random_source[i]]);
	}
	for(int i = 0;i<10;i++)
	{
		ALLEGRO_BITMAP* tmp = al_load_bitmap(minion_name_set[i]);
		minion_menu_source.push_back(tmp);
	}

	for(int i = 0; i<4; i++)
    {
        int n = rand()%10;

        while(RandomNumExist(minion_random_source[n]))
        {
            n = rand()%10;
        }

        minion_random_set[i] = minion_random_source[n];
    }

	ToggleInitial();
}

bool Menu::RandomNumExist(int num)
{
    for(int i = 0; i<10; i++)
    {
        if(num == minion_random_set[i])
        {
            return true;
        }
    }
    return false;
}

void Menu::GainHolyWater(ScoreBoard* scoreboard, int change)
{
	if(holy_water + change >= 0 && holy_water + change <= max_holy_water)
	{
		holy_water += change;
	}

	if(team == red_team)
	{
		scoreboard->Set_Player_1_HolyWater(holy_water);
	}
	else if(team == blue_team)
	{
		scoreboard->Set_Player_2_HolyWater(holy_water);
	}
}

bool Menu::EnoughHolyWater(int type)
{
	if(type < 0 || type >= minion_num)
    {
        return false;
    }
    return (holy_water + needed_holy_water[type] >= 0);
}

void Menu::ChangeHolyWater(ScoreBoard* scoreboard, int type)
{
	holy_water += needed_holy_water[type];

	if(team == red_team)
	{
		scoreboard->Set_Player_1_HolyWater(holy_water);
	}
	else if(team == blue_team)
	{
		scoreboard->Set_Player_2_HolyWater(holy_water);
	}
}

void Menu::setMinionRandomSource(int _minion_random_source[])
{
	for(int i = 0;i<10;i++)
	{
		minion_random_source[i] = _minion_random_source[i];
	}
}

int Menu::MinionSummon(int hotkey)
{

}
