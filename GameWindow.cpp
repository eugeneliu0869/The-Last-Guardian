#include "GameWindow.h"

// constructor and destructor
GameWindow::GameWindow()
{
    if(!al_init())
    {
        show_error_message("Game initialization fail.");
    }

    cout << "Game initializing...\n";

    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / FPS);

    if(display == NULL)
    {
        show_error_message("Game display creation fail.");
    }
    if(event_queue == NULL)
    {
        show_error_message("Game event_queue creation fail.");
    }
    if(timer == NULL)
    {
        show_error_message("Game timer creation fail.");
    }

    al_init_acodec_addon();     // initialize acodec addon
    al_init_font_addon();       // initialize the font addon
    al_init_image_addon();      // initialize the image addon
    al_init_primitives_addon(); // initialize the primitive addon
    al_init_ttf_addon();        // initialize the ttf addon

    al_install_audio();    // install audio event
    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event

    Small_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0);  // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); // load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0);  // load large font
    Giant_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",50,0);  // load giant font

    if(Small_font == NULL || Medium_font == NULL || Large_font == NULL)
    {
        show_error_message("Game font loading fail.");
    }

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    // Initializing the resources
    game_init();
}

GameWindow::~GameWindow()
{

}
// end of constructor and destructor

// debug usage
void
GameWindow::show_error_message(string msg)
{
    cout << msg << endl;

    game_destroy();
    exit(9);
}
// end of debug usage

// detect if mouse hovers over a rectangle
bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
    {
        if(mouse_y >= starty && mouse_y <= starty + height)
        {
            return true;
        }
    }

    return false;
}
// end of detect if mouse hovers over a rectangle

// detect if player's position is in arena field
bool GameWindow::is_in_arena_field(int player, int pos_x, int pos_y)
{
    if(player == 1)
    {
        if(pos_x >= menu_width && pos_x <= menu_width + arena_field_width - player_arena_field_control_grid_width &&
           pos_y >= scoreboard_height && pos_y <= window_height - player_arena_field_control_grid_height)
        {
            return true;
        }
        return false;
    }
    else if(player == 2)
    {
        if(pos_x >= window_width - menu_width - arena_field_width && pos_x <= window_width - menu_width - player_arena_field_control_grid_width &&
           pos_y >= scoreboard_height && pos_y <= window_height - player_arena_field_control_grid_height)
        {
            return true;
        }
        return false;
    }
}

Minion*
GameWindow::create_minion(int selected_minion)
{
    Minion* m = NULL;

    switch(selected_minion)
    {
        case SABER:
            m = new Saber(100, 100, red_team);
            break;
    }

    return m;
}

// game control function
void
GameWindow::game_init()
{
    srand(time(NULL));

    icon = al_load_bitmap("./image/Icon.png");
    background = al_load_bitmap("./image/RunScene/Background.png");

    if(icon == NULL || background == NULL)
    {
        show_error_message("Game run scene images loading fail.");
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(4);

    sample = al_load_sample("./sound/RunScene/StartSound.ogg");
    start_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(start_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(start_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/RunScene/BackgroundSound.ogg");
    background_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(background_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(background_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/RunScene/EffectSound.ogg");
    effect_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(effect_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(effect_sound, al_get_default_mixer());

    sample = al_load_sample("./sound/RunScene/ResultSound.ogg");
    result_sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(result_sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(result_sound, al_get_default_mixer());

    if(start_sound == NULL || background == NULL || effect_sound == NULL || result_sound == NULL)
    {
        show_error_message("Game run scene sounds loading fail.");
    }

    score_board = new ScoreBoard();

    // game control variables initialization
    redraw = false;
    mute = false;
    pause = false;
    back_scene = GAME_INIT;

    // players' interface variables initialization
    holy_water_gain_speed = 60;
    player_1_holy_water_counter = 0;
    player_2_holy_water_counter = 0;
    // end of players' interface variables initialization

    // for debug usage
    Minion* m = create_minion(SABER);
    MinionSet.push_back(m);
    // end of debug usage

    // player 1 initialization
    player_1_arena_field_control_pos_x = menu_width;
    player_1_arena_field_control_pos_y = scoreboard_height;

    player_1_army_1_card_pos_x = player_army_card_horizontal_difference;
    player_1_army_1_card_pos_y = scoreboard_height + player_army_card_top_difference;
    player_1_army_2_card_pos_x = player_army_card_horizontal_difference;
    player_1_army_2_card_pos_y = player_1_army_1_card_pos_y + player_army_card_height + player_army_card_vertical_difference;
    player_1_army_3_card_pos_x = player_army_card_horizontal_difference;
    player_1_army_3_card_pos_y = player_1_army_2_card_pos_y + player_army_card_height + player_army_card_vertical_difference;
    player_1_army_4_card_pos_x = player_army_card_horizontal_difference;
    player_1_army_4_card_pos_y = player_1_army_3_card_pos_y + player_army_card_height + player_army_card_vertical_difference;
    // end of player 1 initialization

    // player 2 initialization
    player_2_arena_field_control_pos_x = window_width - menu_width - arena_field_width;
    player_2_arena_field_control_pos_y = scoreboard_height;

    player_2_army_1_card_pos_x = window_width - menu_width + player_army_card_horizontal_difference;
    player_2_army_1_card_pos_y = scoreboard_height + player_army_card_top_difference;
    player_2_army_2_card_pos_x = window_width - menu_width + player_army_card_horizontal_difference;
    player_2_army_2_card_pos_y = player_2_army_1_card_pos_y + player_army_card_height + player_army_card_vertical_difference;
    player_2_army_3_card_pos_x = window_width - menu_width + player_army_card_horizontal_difference;
    player_2_army_3_card_pos_y = player_2_army_2_card_pos_y + player_army_card_height + player_army_card_vertical_difference;
    player_2_army_4_card_pos_x = window_width - menu_width + player_army_card_horizontal_difference;
    player_2_army_4_card_pos_y = player_2_army_3_card_pos_y + player_army_card_height + player_army_card_vertical_difference;
    // end of player 2 initialization
}

void
GameWindow::game_begin()
{
    cout << "Game start.\n";

    draw_running_animation();
    /*
    al_play_sample_instance(start_sound);
    while(al_get_sample_instance_playing(start_sound));
    {
        al_play_sample_instance(background_sound);
    }
    */
    al_start_timer(timer);
}

void
GameWindow::game_play()
{
    int msg = -1;

    StartScene* start_scene = new StartScene();
    SettingScene* setting_scene = new SettingScene();
    SelectScene* select_scene = new SelectScene();
    PauseScene* pause_scene = new PauseScene();
    ResultScene* result_scene = new ResultScene();
    ExitScene* exit_scene = new ExitScene();

    while(msg != GAME_EXIT)
    {
        switch(msg)
        {
            case GAME_INIT:
                msg = game_start_scene(start_scene);
                break;
            case GAME_SETTING:
                msg = game_setting_scene(setting_scene);
                break;
            case GAME_SELECT:
                msg = game_select_scene(select_scene);
                break;
            case GAME_BEGIN:
                game_begin();
                msg = GAME_CONTINUE;
                break;
            case GAME_CONTINUE:
                msg = game_run_scene();
                break;
            case GAME_PAUSE:
                msg = game_pause_scene(pause_scene);
                break;
            case GAME_RESULT:
                msg = game_result_scene(result_scene);
                break;
            /*case GAME_EXIT:
                msg = game_exit_scene(exit_scene);
                break;*/
        }
    }

    delete start_scene;
    delete setting_scene;
    delete select_scene;
    delete pause_scene;
    delete result_scene;
    delete exit_scene;

    show_error_message("Game terminate.");
}

void
GameWindow::game_reset()
{
    // game control variables reset
    redraw = false;
    mute = false;
    pause = false;
    back_scene = GAME_INIT;

    // score board reset
    score_board->Reset();

    // stop sample instance
    al_stop_sample_instance(start_sound);
    al_stop_sample_instance(background_sound);
    al_stop_sample_instance(effect_sound);
    al_stop_sample_instance(result_sound);

    // stop timer
    al_stop_timer(timer);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_font(Small_font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);

    al_destroy_event_queue(event_queue);

    al_destroy_timer(timer);

    al_destroy_sample(sample);
    al_destroy_sample_instance(start_sound);
    al_destroy_sample_instance(background_sound);
    al_destroy_sample_instance(effect_sound);
    al_destroy_sample_instance(result_sound);
}
// end of game control function

// draw running animation
int
GameWindow::draw_running_animation()
{
    // for the debug usage
    // draw menu
    al_draw_filled_rectangle(0, scoreboard_height, menu_width, window_height, al_map_rgb(150, 150, 150));
    al_draw_filled_rectangle(window_width - menu_width, scoreboard_height, window_width, window_height, al_map_rgb(150, 150, 150));

    // draw arena field and river
    al_draw_filled_rectangle(menu_width, scoreboard_height,
                             menu_width + arena_field_width, window_height, al_map_rgb(0, 205, 0));
    al_draw_filled_rectangle(menu_width + arena_field_width, scoreboard_height,
                             menu_width + arena_field_width + arena_river_width, window_height, al_map_rgb(135, 206, 235));
    al_draw_filled_rectangle(window_width - menu_width - arena_field_width, scoreboard_height,
                             window_width - menu_width, window_height, al_map_rgb(0, 205, 0));
    // end of for the debug usage

    // draw score board
    score_board->Draw();

    for(auto i : MinionSet)
    {
        i->Draw();
    }

    // draw players' arena control display
    al_draw_text(Small_font, player_1_color, player_1_arena_field_control_pos_x, player_1_arena_field_control_pos_y - 15, 0, "p1");
    al_draw_rectangle(player_1_arena_field_control_pos_x,
                      player_1_arena_field_control_pos_y,
                      player_1_arena_field_control_pos_x + player_arena_field_control_grid_width,
                      player_1_arena_field_control_pos_y + player_arena_field_control_grid_height,
                      player_1_color, player_arena_field_control_display_thickness);

    al_draw_text(Small_font, player_2_color, player_2_arena_field_control_pos_x, player_2_arena_field_control_pos_y - 15, 0, "p2");
    al_draw_rectangle(player_2_arena_field_control_pos_x,
                      player_2_arena_field_control_pos_y,
                      player_2_arena_field_control_pos_x + player_arena_field_control_grid_width,
                      player_2_arena_field_control_pos_y + player_arena_field_control_grid_height,
                      player_2_color, player_arena_field_control_display_thickness);

    // draw players' army card
    al_draw_text(Small_font, player_1_color, player_1_army_1_card_pos_x, player_1_army_1_card_pos_y - 15, 0, "B");
    al_draw_rectangle(player_1_army_1_card_pos_x, player_1_army_1_card_pos_y,
                      player_1_army_1_card_pos_x + player_army_card_width, player_1_army_1_card_pos_y + player_army_card_height,
                      player_1_color, player_army_card_display_thickness);
    al_draw_text(Small_font, player_1_color, player_1_army_2_card_pos_x, player_1_army_2_card_pos_y - 15, 0, "N");
    al_draw_rectangle(player_1_army_2_card_pos_x, player_1_army_2_card_pos_y,
                      player_1_army_2_card_pos_x + player_army_card_width, player_1_army_2_card_pos_y + player_army_card_height,
                      player_1_color, player_army_card_display_thickness);
    al_draw_text(Small_font, player_1_color, player_1_army_3_card_pos_x, player_1_army_3_card_pos_y - 15, 0, "M");
    al_draw_rectangle(player_1_army_3_card_pos_x, player_1_army_3_card_pos_y,
                      player_1_army_3_card_pos_x + player_army_card_width, player_1_army_3_card_pos_y + player_army_card_height,
                      player_1_color, player_army_card_display_thickness);
    al_draw_text(Small_font, player_1_color, player_1_army_4_card_pos_x, player_1_army_4_card_pos_y - 15, 0, "G");
    al_draw_rectangle(player_1_army_4_card_pos_x, player_1_army_4_card_pos_y,
                      player_1_army_4_card_pos_x + player_army_card_width, player_1_army_4_card_pos_y + player_army_card_height,
                      player_1_color, player_army_card_display_thickness);

    al_draw_text(Small_font, player_2_color, player_2_army_1_card_pos_x, player_2_army_1_card_pos_y - 15, 0, "1");
    al_draw_rectangle(player_2_army_1_card_pos_x, player_1_army_1_card_pos_y,
                      player_2_army_1_card_pos_x + player_army_card_width, player_2_army_1_card_pos_y + player_army_card_height,
                      player_2_color, player_army_card_display_thickness);
    al_draw_text(Small_font, player_2_color, player_2_army_2_card_pos_x, player_2_army_2_card_pos_y - 15, 0, "2");
    al_draw_rectangle(player_2_army_2_card_pos_x, player_1_army_2_card_pos_y,
                      player_2_army_2_card_pos_x + player_army_card_width, player_2_army_2_card_pos_y + player_army_card_height,
                      player_2_color, player_army_card_display_thickness);
    al_draw_text(Small_font, player_2_color, player_2_army_3_card_pos_x, player_2_army_3_card_pos_y - 15, 0, "3");
    al_draw_rectangle(player_2_army_3_card_pos_x, player_1_army_3_card_pos_y,
                      player_2_army_3_card_pos_x + player_army_card_width, player_2_army_3_card_pos_y + player_army_card_height,
                      player_2_color, player_army_card_display_thickness);
    al_draw_text(Small_font, player_2_color, player_2_army_4_card_pos_x, player_2_army_4_card_pos_y - 15, 0, "4");
    al_draw_rectangle(player_2_army_4_card_pos_x, player_1_army_4_card_pos_y,
                      player_2_army_4_card_pos_x + player_army_card_width, player_2_army_4_card_pos_y + player_army_card_height,
                      player_2_color, player_army_card_display_thickness);

    al_flip_display();
}
// end of draw running animation

// game update
int
GameWindow::game_update()
{
    vector<Minion*>::iterator it;

    for(it = MinionSet.begin(); it != MinionSet.end(); it++)
    {
        (*it)->findClosestTower(1000, 300);
        (*it)->find_way();
        (*it)->Move();
    }
}
// end of game update

// game scene
int
GameWindow::game_start_scene(StartScene* start_scene)
{
    int msg = GAME_INIT;

    if(!start_scene->get_initial())
    {
        start_scene->SceneInit();
        start_scene->toggle_initial();
    }
    start_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_start_scene(start_scene);
    }
    return msg;
}

int
GameWindow::game_setting_scene(SettingScene* setting_scene)
{
    int msg = GAME_SETTING;

    if(!setting_scene->get_initial())
    {
        setting_scene->SceneInit();
        setting_scene->toggle_initial();
    }
    setting_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_setting_scene(setting_scene);
    }
    return msg;
}

int
GameWindow::game_select_scene(SelectScene* select_scene)
{
    int msg = GAME_SELECT;

    select_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_select_scene(select_scene);
    }
    return msg;
}

int
GameWindow::game_run_scene()
{
    int msg = GAME_CONTINUE;

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_run_scene();
    }
    return msg;
}

int
GameWindow::game_pause_scene(PauseScene* pause_scene)
{
    int msg = GAME_PAUSE;

    if(!pause_scene->get_initial())
    {
        pause_scene->SceneInit();
        pause_scene->toggle_initial();
    }

    pause_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_pause_scene(pause_scene);
    }
    return msg;
}

int
GameWindow::game_result_scene(ResultScene* result_scene)
{
    int msg = GAME_RESULT;

    result_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_result_scene(result_scene);
    }
    return msg;
}

int
GameWindow::game_exit_scene(ExitScene* exit_scene)
{
    int msg = GAME_EXIT;

    exit_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_exit_scene(exit_scene);
    }
    return msg;
}
// end of game scene

// game process of update event
int
GameWindow::process_event_start_scene(StartScene* start_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            back_scene = GAME_INIT;
            return start_scene->LabelSelected(mouse_x, mouse_y);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        start_scene->LabelMouseHover(mouse_x, mouse_y);
    }

    return GAME_INIT;
}

int
GameWindow::process_event_setting_scene(SettingScene* setting_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
    {
        if(event.mouse.button == 1)
        {
            if(setting_scene->background_sound->isClicked(mouse_x, mouse_y))
            {
                setting_scene->background_sound->toggleDrag();
            }
            else if(setting_scene->effect_sound->isClicked(mouse_x, mouse_y))
            {
                setting_scene->effect_sound->toggleDrag();
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            if(setting_scene->background_sound->isDragged())
            {
                setting_scene->background_sound->toggleDrag();
            }
            else if(setting_scene->effect_sound->isDragged())
            {
                setting_scene->effect_sound->toggleDrag();
            }

            if(setting_scene->LabelSelected(mouse_x, mouse_y) == GAME_BACK)
            {
                return back_scene;
            }
            return setting_scene->LabelSelected(mouse_x, mouse_y);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        setting_scene->LabelMouseHover(mouse_x, mouse_y);

        if(setting_scene->background_sound->isDragged())
        {
            al_set_sample_instance_gain(background_sound, setting_scene->background_sound->Drag(mouse_x, mouse_y));
        }
        else if(setting_scene->effect_sound->isDragged())
        {
            al_set_sample_instance_gain(effect_sound, setting_scene->effect_sound->Drag(mouse_x, mouse_y));
        }
    }

    return GAME_SETTING;
}

int
GameWindow::process_event_select_scene(SelectScene* select_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            return select_scene->LabelSelected(mouse_x, mouse_y);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        select_scene->LabelMouseHover(mouse_x, mouse_y);
    }

    return GAME_SELECT;
}

int
GameWindow::process_event_run_scene()
{
    al_wait_for_event(event_queue, &event);

    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER)
    {
        if(event.timer.source == timer)
        {
            redraw = true;

            if(player_1_holy_water_counter == 0)
            {
                score_board->Change_Player_1_HolyWater(1);
            }
            player_1_holy_water_counter = (player_1_holy_water_counter + 1) % holy_water_gain_speed;

            if(player_2_holy_water_counter == 0)
            {
                score_board->Change_Player_2_HolyWater(1);
            }
            player_2_holy_water_counter = (player_2_holy_water_counter + 1) % holy_water_gain_speed;
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        // escape key event
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        } // end of escape key event
        // pause key event
        else if(event.keyboard.keycode == ALLEGRO_KEY_P)
        {
                pause = !pause;

                if(pause)
                {
                    al_stop_timer(timer);
                    back_scene = GAME_CONTINUE;
                    return GAME_PAUSE;
                }
                else
                {
                    al_start_timer(timer);
                }
        } // end of pause key event
        // player 1 key event
        else if(event.keyboard.keycode == ALLEGRO_KEY_W) // player 1 key up
        {
            if(is_in_arena_field(1, player_1_arena_field_control_pos_x,
                                    player_1_arena_field_control_pos_y - player_arena_field_control_grid_height))
            {
                player_1_arena_field_control_pos_y -= player_arena_field_control_grid_height;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_S) // player 1 key down
        {
            if(is_in_arena_field(1, player_1_arena_field_control_pos_x,
                                    player_1_arena_field_control_pos_y + player_arena_field_control_grid_height))
            {
                player_1_arena_field_control_pos_y += player_arena_field_control_grid_height;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_A) // player 1 key left
        {
            if(is_in_arena_field(1, player_1_arena_field_control_pos_x - player_arena_field_control_grid_width,
                                    player_1_arena_field_control_pos_y))
            {
                player_1_arena_field_control_pos_x -= player_arena_field_control_grid_width;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_D) // player 1 key up
        {
            if(is_in_arena_field(1, player_1_arena_field_control_pos_x + player_arena_field_control_grid_width,
                                    player_1_arena_field_control_pos_y))
            {
                player_1_arena_field_control_pos_x += player_arena_field_control_grid_width;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_B) // player 1 army 1 card hot key
        {
            // contact with menu
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_N) // player 1 army 2 card hot key
        {
            // contact with menu
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_M) // player 1 army 3 card hot key
        {
            // contact with menu
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_G) // player 1 army 4 card hot key
        {
            // contact with menu
        }
        // end of player 1 key event
        // player 2 key event
        else if(event.keyboard.keycode == ALLEGRO_KEY_UP) // player 2 key up
        {
            if(is_in_arena_field(2, player_2_arena_field_control_pos_x,
                                    player_2_arena_field_control_pos_y - player_arena_field_control_grid_height))
            {
                player_2_arena_field_control_pos_y -= player_arena_field_control_grid_height;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_DOWN) // player 2 key down
        {
            if(is_in_arena_field(2, player_2_arena_field_control_pos_x,
                                    player_2_arena_field_control_pos_y + player_arena_field_control_grid_height))
            {
                player_2_arena_field_control_pos_y += player_arena_field_control_grid_height;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_LEFT) // player 2 key left
        {
            if(is_in_arena_field(2, player_2_arena_field_control_pos_x - player_arena_field_control_grid_width,
                                    player_2_arena_field_control_pos_y))
            {
                player_2_arena_field_control_pos_x -= player_arena_field_control_grid_width;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT) // player 2 key up
        {
            if(is_in_arena_field(2, player_2_arena_field_control_pos_x + player_arena_field_control_grid_width,
                                    player_2_arena_field_control_pos_y))
            {
                player_2_arena_field_control_pos_x += player_arena_field_control_grid_width;
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_1) // player 2 army 1 card hot key
        {
            // contact with menu
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_2) // player 2 army 2 card hot key
        {
            // contact with menu
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_3) // player 2 army 3 card hot key
        {
            // contact with menu
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_4) // player 2 army 4 card hot key
        {
            // contact with menu
        }
        // end of player 2 key event
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;
    }

    if(redraw)
    {
        game_update();
        draw_running_animation();
        redraw = false;
    }

    return GAME_CONTINUE;
}

int
GameWindow::process_event_pause_scene(PauseScene* pause_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_P)
        {
            pause = !pause;

            if(pause)
            {
                al_stop_timer(timer);
            }
            else
            {
                al_start_timer(timer);
                back_scene = GAME_INIT;
                cout << "Game continue.\n";
                return GAME_CONTINUE;
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            if(pause_scene->LabelSelected(mouse_x, mouse_y) == GAME_CONTINUE)
            {
                pause = !pause;
                al_start_timer(timer);
                back_scene = GAME_INIT;
                cout << "Game continue.\n";
                return GAME_CONTINUE;
            }
            else if(pause_scene->LabelSelected(mouse_x, mouse_y) == GAME_SETTING)
            {
                back_scene = GAME_PAUSE;
                return GAME_SETTING;
            }
            else if(pause_scene->LabelSelected(mouse_x, mouse_y) == GAME_BACK)
            {
                pause = !pause;
                al_start_timer(timer);
                back_scene = GAME_INIT;
                cout << "Game continue.\n";
                return GAME_CONTINUE;
            }
            else
            {
                back_scene = GAME_PAUSE;
                return pause_scene->LabelSelected(mouse_x, mouse_y);
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        pause_scene->LabelMouseHover(mouse_x, mouse_y);
    }

    return GAME_PAUSE;
}

int
GameWindow::process_event_result_scene(ResultScene* result_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            return result_scene->LabelSelected(mouse_x, mouse_y);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        result_scene->LabelMouseHover(mouse_x, mouse_y);
    }

    return GAME_RESULT;
}

int
GameWindow::process_event_exit_scene(ExitScene* exit_scene)
{
    al_wait_for_event(event_queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
    {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
        {
            return GAME_EXIT;
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
    {
        if(event.mouse.button == 1)
        {
            return exit_scene->LabelSelected(mouse_x, mouse_y);
        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
    {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;

        exit_scene->LabelMouseHover(mouse_x, mouse_y);
    }

    return GAME_EXIT;
}
// end of game process of update event
