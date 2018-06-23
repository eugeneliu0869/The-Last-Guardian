#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <math.h>
#include <vector>
#include <set>
#include <list>
using namespace std;

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_PAUSE 4
#define GAME_RESULT 5
#define GAME_RESET 6
#define GAME_EXIT 7
#define GAME_TERMINATE 8
#define GAME_BACK 9

#define window_width 1200
#define window_height 600

#define scoreboard_width 1200
#define scoreboard_height 100

#define menu_width 80
#define menu_height 500

#define arena_field_width 500
#define arena_field_height 500
#define arena_river_width 40

#define RIVER_WIDTH 40
#define BRIDGE_WIDTH 100
#define BRIDGE_HEIGHT 30
#define UPPER_BRIDGE_Y 100
#define LOWER_BRIDGE_Y 400

#define grid_width 5
#define grid_height 5
#define NumOfGrid (arena_field_width / grid_width) * (arena_field_height / grid_height)

#define player_1_color al_map_rgb(255, 69, 0)
#define player_2_color al_map_rgb(205, 0, 205)

#define max_holy_water 10

#define minion_num 30

extern char ArmyClass[][30];

enum {red_team = 0, blue_team};
enum {SABER = 0};

#endif // GLOBAL_H_INCLUDED
