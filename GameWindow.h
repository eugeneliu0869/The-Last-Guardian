#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED

#include "global.h"
#include "Map.h"
#include "Menu.h"
#include "Minion.h"
#include "Saber.h"
#include "RangeAttack.h"
#include "Slider.h"
#include "StartScene.h"
#include "SettingScene.h"
#include "SelectScene.h"
#include "PauseScene.h"
#include "ResultScene.h"
#include "ExitScene.h"
#include "ScoreBoard.h"

#define player_arena_field_control_grid_width 50
#define player_arena_field_control_grid_height 50
#define player_arena_field_control_max_pos_x = arena_field_width / player_control_grid_width
#define player_arena_field_control_max_pos_y = arena_field_height / player_control_grid_height
#define player_arena_field_control_display_thickness 2

#define player_army_card_width 60
#define player_army_card_height 60
#define player_army_card_horizontal_difference 10
#define player_army_card_top_difference 70
#define player_army_card_vertical_difference 40
#define player_army_card_display_thickness 2

// clock rate
const float FPS = 60;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // destructor
    ~GameWindow();

    // debug usage
    void show_error_message(string msg);

    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);

    // detect if player's position is in arena field
    bool is_in_arena_field(int, int, int);

    // create minion
    Minion* create_minion(int);

    // set game sounds' volume
    void set_background_sound_volume(double);
    void set_effect_sound_volume(double);

    // game control function
    void game_init();
    void game_begin();
    void game_play();
    void game_reset();
    void game_destroy();

    // draw running animation
    int draw_running_animation();

    // game update
    int game_update();

    // game scene
    int game_start_scene(StartScene*);
    int game_setting_scene(SettingScene*);
    int game_select_scene(SelectScene*);
    int game_run_scene();
    int game_pause_scene(PauseScene*);
    int game_result_scene(ResultScene*);
    int game_exit_scene(ExitScene*);

    // game process of update event
    int process_event_start_scene(StartScene*);
    int process_event_setting_scene(SettingScene*);
    int process_event_select_scene(SelectScene*);
    int process_event_run_scene();
    int process_event_pause_scene(PauseScene*);
    int process_event_result_scene(ResultScene*);
    int process_event_exit_scene(ExitScene*);

    // game control variables
    bool redraw = false;
    bool mute = false;
    bool pause = false;
    int back_scene = GAME_INIT;

private:
    ScoreBoard* score_board;
    Menu* player_1_menu;
    Menu* player_2_menu;

    ALLEGRO_DISPLAY* display = NULL;

    ALLEGRO_BITMAP* icon = NULL;
    ALLEGRO_BITMAP* background = NULL;
    ALLEGRO_BITMAP* river = NULL;
    ALLEGRO_BITMAP* bridge = NULL;

    ALLEGRO_FONT* Small_font = NULL;
    ALLEGRO_FONT* Medium_font = NULL;
    ALLEGRO_FONT* Large_font = NULL;
    ALLEGRO_FONT* Giant_font = NULL;

    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;

    ALLEGRO_TIMER* timer = NULL;

    ALLEGRO_SAMPLE* sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE* start_sound = NULL; // classified as background sound
    ALLEGRO_SAMPLE_INSTANCE* background_sound = NULL; // classified as background sound
    ALLEGRO_SAMPLE_INSTANCE* effect_sound = NULL; // classified as effect sound
    ALLEGRO_SAMPLE_INSTANCE* result_sound = NULL; // classified as background sound

    // the map that players choose, counting from 1 to ...
    int game_map;

    // players' interface variables
    int holy_water_gain_speed;
    int player_1_holy_water_counter;
    int player_2_holy_water_counter;

    // mouse control
    float mouse_x, mouse_y;

    vector<Minion*> MinionSet;

    // player 1 is at left, player 2 is at right
    // player 1 control
    int player_1_minion_selected_source[10];
    int player_1_arena_field_control_pos_x;
    int player_1_arena_field_control_pos_y;

    // player 2 control
    int player_2_minion_selected_source[10];
    int player_2_arena_field_control_pos_x;
    int player_2_arena_field_control_pos_y;
};

#endif // GAMEWINDOW_H_INCLUDED
