#include "GameWindow.h"

// constructor and destructor
GameWindow::GameWindow()
{
    if(!al_init())
    {
        show_error_message("Allegro 5 initialization fail.");
    }

    // For creating a new map, you need to put the needed images into the folder "./image/create_new_map", and then turn on the following comments.
    // After creating the new map, you need to cut it into proper size (140 pixel * 50 pixel), and then put it into the folder "./image/SelectScene".
    /*
    cout << "You are now in the map creating mode. If you want to go back to the playing mode, please turn off the map_creating codes as comments.\n";

    ALLEGRO_DISPLAY* _display = NULL;
    ALLEGRO_BITMAP* _background = NULL, * _river = NULL, * _bridge = NULL;

    _display = al_create_display(1040, 500);

    al_init_acodec_addon();
    al_init_image_addon();
    al_init_primitives_addon();

    _background = al_load_bitmap("./image/create_new_map/Background.png"); // background's size should be (1040 pixel * 500 pixel)
    _river = al_load_bitmap("./image/create_new_map/River.png"); // river's size should be (40 pixel * 500 pixel)
    _bridge = al_load_bitmap("./image/create_new_map/Bridge.png"); // bridge's size should be (100 pixel * 30 pixel)

    al_draw_bitmap(_background, 0, 0, 0);
    al_draw_bitmap(_river, 520 - 40/2, 0, 0);
    al_draw_bitmap(_bridge, 520 - 100/2, 100 - 3/2, 0);
    al_draw_bitmap(_bridge, 520 - 100/2, 400 - 3/2, 0);

    al_flip_display();

    system("pause");
    exit(9);
    */

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
    delete score_board;
    delete player_1_menu;
    delete player_2_menu;
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
GameWindow::create_minion(int selected_minion, int team, int pos_x, int pos_y)
{
    Minion* m = NULL;

    switch(selected_minion)
    {
        case SABER:
            m = new Saber(pos_x, pos_y, team);
            break;
    }

    return m;
}

// set game sounds' volume
void GameWindow::set_background_sound_volume(double volume)
{
    background_sound_volume = volume;
}

void GameWindow::set_effect_sound_volume(double volume)
{
    effect_sound_volume = volume;
}
// end of set game sounds' volume

// set map
void GameWindow::set_map(int _game_map)
{
    game_map = _game_map;

    if(background != NULL)
    {
        al_destroy_bitmap(background);
    }
    if(river != NULL)
    {
        al_destroy_bitmap(river);
    }
    if(bridge != NULL)
    {
        al_destroy_bitmap(bridge);
    }

    char background_buffer[50], river_buffer[50], bridge_buffer[50];

    sprintf(background_buffer, "./image/RunScene/Map_%d/Background.png", game_map);
    sprintf(river_buffer, "./image/RunScene/Map_%d/River.png", game_map);
    sprintf(bridge_buffer, "./image/RunScene/Map_%d/Bridge.png", game_map);

    background = al_load_bitmap(background_buffer);
    river = al_load_bitmap(river_buffer);
    bridge = al_load_bitmap(bridge_buffer);
}
// end of set map

// game control function
void
GameWindow::game_init()
{
    srand(time(NULL));

    score_board = new ScoreBoard();
    player_1_menu = new Menu(red_team, score_board);
    player_2_menu = new Menu(blue_team, score_board);

    start_scene = new StartScene();
    setting_scene = new SettingScene();
    select_scene = new SelectScene();
    pause_scene = new PauseScene();
    result_scene = new ResultScene();
    exit_scene = new ExitScene();

    icon = al_load_bitmap("./image/Icon.png");

    set_map(1);

    if(icon == NULL || background == NULL || river == NULL || bridge == NULL)
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

    // tower initialization
    Tower* t;

    // create red team's towers
    t = new MinorTower(menu_width + upper_minortower_away_from_side, scoreboard_height + upper_minortower_pos_y);
    Red_Team_Tower_Set.push_back(t);
    t = new MajorTower(menu_width + majortower_away_from_side, scoreboard_height + majortower_pos_y);
    Red_Team_Tower_Set.push_back(t);
    t = new MinorTower(menu_width + lower_minortower_away_from_side, scoreboard_height + lower_minortower_pos_y);
    Red_Team_Tower_Set.push_back(t);

    // create blue team's towers
    t = new MinorTower(window_width - menu_width - upper_minortower_away_from_side, scoreboard_height + upper_minortower_pos_y);
    Blue_Team_Tower_Set.push_back(t);
    t = new MajorTower(window_width - menu_width - majortower_away_from_side, scoreboard_height + majortower_pos_y);
    Blue_Team_Tower_Set.push_back(t);
    t = new MinorTower(window_width - menu_width - lower_minortower_away_from_side, scoreboard_height + lower_minortower_pos_y);
    Blue_Team_Tower_Set.push_back(t);
    // end of tower initialization

    // for the debug usage
    player_1_minion_selected_source[0] = SABER;
    player_1_minion_selected_source[1] = SABER1;
    player_1_minion_selected_source[2] = SABER2;
    player_1_minion_selected_source[3] = SABER3;
    player_1_minion_selected_source[4] = SABER4;
    player_1_minion_selected_source[5] = SABER5;
    player_1_minion_selected_source[6] = SABER6;
    player_1_minion_selected_source[7] = SABER7;
    player_1_minion_selected_source[8] = SABER8;
    player_1_minion_selected_source[9] = SABER9;
    player_1_menu->Initial(player_1_minion_selected_source);

    player_2_minion_selected_source[0] = SABER;
    player_2_minion_selected_source[1] = SABER1;
    player_2_minion_selected_source[2] = SABER2;
    player_2_minion_selected_source[3] = SABER3;
    player_2_minion_selected_source[4] = SABER4;
    player_2_minion_selected_source[5] = SABER5;
    player_2_minion_selected_source[6] = SABER6;
    player_2_minion_selected_source[7] = SABER7;
    player_2_minion_selected_source[8] = SABER8;
    player_2_minion_selected_source[9] = SABER9;
    player_2_menu->Initial(player_2_minion_selected_source);
    // end of for the debug usage

    // player 1 initialization
    player_1_arena_field_control_pos_x = menu_width;
    player_1_arena_field_control_pos_y = scoreboard_height;
    // end of player 1 initialization

    // player 2 initialization
    player_2_arena_field_control_pos_x = window_width - menu_width - player_arena_field_control_grid_width;
    player_2_arena_field_control_pos_y = scoreboard_height;
    // end of player 2 initialization
}

void
GameWindow::game_begin()
{
    cout << "Game start.\n";

    draw_running_animation();

    al_play_sample_instance(background_sound);

    al_start_timer(timer);
}

void
GameWindow::game_play()
{
    int msg = -1;

    while(msg != GAME_EXIT)
    {
        al_set_sample_instance_gain(start_sound, background_sound_volume);
        al_set_sample_instance_gain(background_sound, background_sound_volume);
        al_set_sample_instance_gain(effect_sound, effect_sound_volume);
        al_set_sample_instance_gain(result_sound, background_sound_volume);

        switch(msg)
        {
            case GAME_INIT:
                msg = game_start_scene();
                break;
            case GAME_SETTING:
                msg = game_setting_scene();
                break;
            case GAME_SELECT:
                msg = game_select_scene();
                break;
            case GAME_BEGIN:
                game_begin();
                msg = GAME_CONTINUE;
                break;
            case GAME_CONTINUE:
                msg = game_run_scene();
                break;
            case GAME_PAUSE:
                msg = game_pause_scene();
                break;
            case GAME_RESULT:
                msg = game_result_scene();
                break;
            /*case GAME_EXIT:
                msg = game_exit_scene();
                break;*/
        }
    }

    show_error_message("Game terminate.");
}

void
GameWindow::game_reset()
{
    // game map reset
    set_map(1);

    // game control variables reset
    redraw = false;
    mute = false;
    pause = false;
    back_scene = GAME_INIT;

    // select scene reset
    select_scene->Reset();

    // players' interface variables reset
    holy_water_gain_speed = 60;
    player_1_holy_water_counter = 0;
    player_2_holy_water_counter = 0;

    // towers reset
    for(auto i : Red_Team_Tower_Set)
    {
        delete i;
    }
    for(auto i : Blue_Team_Tower_Set)
    {
        delete i;
    }

    Tower* t;

    // create red team's towers
    t = new MinorTower(menu_width + upper_minortower_away_from_side, scoreboard_height + upper_minortower_pos_y);
    Red_Team_Tower_Set.push_back(t);
    t = new MajorTower(menu_width + majortower_away_from_side, scoreboard_height + majortower_pos_y);
    Red_Team_Tower_Set.push_back(t);
    t = new MinorTower(menu_width + lower_minortower_away_from_side, scoreboard_height + lower_minortower_pos_y);
    Red_Team_Tower_Set.push_back(t);

    // create blue team's towers
    t = new MinorTower(window_width - menu_width - upper_minortower_away_from_side, scoreboard_height + upper_minortower_pos_y);
    Blue_Team_Tower_Set.push_back(t);
    t = new MajorTower(window_width - menu_width - majortower_away_from_side, scoreboard_height + majortower_pos_y);
    Blue_Team_Tower_Set.push_back(t);
    t = new MinorTower(window_width - menu_width - lower_minortower_away_from_side, scoreboard_height + lower_minortower_pos_y);
    Blue_Team_Tower_Set.push_back(t);
    // end of tower reset

    // score board reset
    score_board->Reset();

    // menu reset
    player_1_menu->Reset();
    player_2_menu->Reset();

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
    al_destroy_bitmap(river);
    al_destroy_bitmap(bridge);

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

    delete score_board;
    delete player_1_menu;
    delete player_2_menu;

    delete start_scene;
    delete setting_scene;
    delete select_scene;
    delete pause_scene;
    delete result_scene;
    delete exit_scene;
}
// end of game control function

// draw running animation
int
GameWindow::draw_running_animation()
{
    // draw map
    al_draw_bitmap(background, menu_width, scoreboard_height, 0);
    al_draw_bitmap(river, menu_width + arena_field_width, scoreboard_height, 0);
    al_draw_bitmap(bridge, window_width/2 - BRIDGE_WIDTH/2, scoreboard_height + UPPER_BRIDGE_Y - BRIDGE_HEIGHT/2, 0); // draw upper bridge
    al_draw_bitmap(bridge, window_width/2 - BRIDGE_WIDTH/2, scoreboard_height + LOWER_BRIDGE_Y - BRIDGE_HEIGHT/2, 0); // draw lower bridge

    // draw score board
    score_board->Draw();

    //cout << "scoreboard->p1: " << score_board->Get_Player_1_HolyWater() << endl;
    //cout << "scoreboard->p2: " << score_board->Get_Player_2_HolyWater() << endl;

    // draw players' menu
    player_1_menu->Draw();
    player_2_menu->Draw();

    //cout << "menu->p1: " << player_1_menu->getHolyWater() << endl;
    //cout << "menu->p2: " << player_2_menu->getHolyWater() << endl;

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

    // draw minions
    for(auto i : Red_Team_Minion_Set)
    {
        i->Draw();
    }
    for(auto i : Blue_Team_Minion_Set)
    {
        i->Draw();
    }

    // draw towers
    for(auto i : Red_Team_Tower_Set)
    {
        i->Draw();
    }
    for(auto i : Blue_Team_Tower_Set)
    {
        i->Draw();
    }

    al_flip_display();
}
// end of draw running animation

// game update
int
GameWindow::game_update()
{
    vector<Minion*>::iterator mit;

    for(mit = Red_Team_Minion_Set.begin(); mit != Red_Team_Minion_Set.end(); mit++)
    {
        (*mit)->findClosestTower(1000, 300); // for the debug usage
        (*mit)->find_way();
        (*mit)->Move();
    }
    for(mit = Blue_Team_Minion_Set.begin(); mit != Blue_Team_Minion_Set.end(); mit++)
    {
        (*mit)->findClosestTower(300, 300); // for the debug usage
        (*mit)->find_way();
        (*mit)->Move();
    }

    // checking all the tower's working status
    vector<Tower*>::iterator tit;

    // for red team towers -> blue_team_minions
    for(tit = Red_Team_Tower_Set.begin(); tit != Red_Team_Tower_Set.end(); tit++)
    {
        Tower* t = (*tit);

        for(int i = 0; i<Blue_Team_Minion_Set.size(); i++)
        {
            Minion* m = Blue_Team_Minion_Set[i];

            if(t->DetectAttack(m))
            {
                t->ResetAttackCounter();
                break;
            }
        }
    }

    for(int i = 0; i<Blue_Team_Minion_Set.size(); i++)
    {
        bool isDestroyed = false;
        Minion* m = Blue_Team_Minion_Set[i];

        for(tit = Red_Team_Tower_Set.begin(); tit != Red_Team_Tower_Set.end(); tit++)
        {
            Tower* t = (*tit);

            if(t->TriggerAttack(m))
            {
                isDestroyed = true;
                break;
            }
        }

        if(isDestroyed)
        {
            Minion* m = Blue_Team_Minion_Set[i];

            Blue_Team_Minion_Set.erase(Blue_Team_Minion_Set.begin() + i);
            i--;
            delete m;
        }
    }

    for(tit = Red_Team_Tower_Set.begin(); tit != Red_Team_Tower_Set.end(); tit++)
    {
        Tower* t = (*tit);

        t->UpdateAttack();
    }
    // end of for red team towers -> blue_team_minions
    // for blue team towers -> red_team_minions
    for(tit = Blue_Team_Tower_Set.begin(); tit != Blue_Team_Tower_Set.end(); tit++)
    {
        Tower* t = (*tit);

        for(int i = 0; i<Red_Team_Minion_Set.size(); i++)
        {
            Minion* m = Red_Team_Minion_Set[i];

            if(t->DetectAttack(m))
            {
                t->ResetAttackCounter();
                break;
            }
        }
    }

    for(int i = 0; i<Red_Team_Minion_Set.size(); i++)
    {
        bool isDestroyed = false;
        Minion* m = Red_Team_Minion_Set[i];

        for(tit = Blue_Team_Tower_Set.begin(); tit != Blue_Team_Tower_Set.end(); tit++)
        {
            Tower* t = (*tit);

            if(t->TriggerAttack(m))
            {
                isDestroyed = true;
                break;
            }
        }

        if(isDestroyed)
        {
            Minion* m = Red_Team_Minion_Set[i];

            Red_Team_Minion_Set.erase(Red_Team_Minion_Set.begin() + i);
            i--;
            delete m;
        }
    }

    for(tit = Blue_Team_Tower_Set.begin(); tit != Blue_Team_Tower_Set.end(); tit++)
    {
        Tower* t = (*tit);

        t->UpdateAttack();
    }
    // end of for blue team towers -> red_team_minions
    // end of checking all the tower's working status
}
// end of game update

// game scene
int
GameWindow::game_start_scene()
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
        msg = process_event_start_scene();
    }
    return msg;
}

int
GameWindow::game_setting_scene()
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
        msg = process_event_setting_scene();
    }
    return msg;
}

int
GameWindow::game_select_scene()
{
    int msg = GAME_SELECT;

    if(!select_scene->get_initial())
    {
        select_scene->SceneInit();
        select_scene->toggle_initial();
    }
    select_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_select_scene();
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
GameWindow::game_pause_scene()
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
        msg = process_event_pause_scene();
    }
    return msg;
}

int
GameWindow::game_result_scene()
{
    int msg = GAME_RESULT;

    result_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_result_scene();
    }
    return msg;
}

int
GameWindow::game_exit_scene()
{
    int msg = GAME_EXIT;

    exit_scene->Draw();

    if(!al_is_event_queue_empty(event_queue))
    {
        msg = process_event_exit_scene();
    }
    return msg;
}
// end of game scene

// game process of update event
int
GameWindow::process_event_start_scene()
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
GameWindow::process_event_setting_scene()
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
            set_background_sound_volume(setting_scene->background_sound->Drag(mouse_x, mouse_y));
        }
        else if(setting_scene->effect_sound->isDragged())
        {
            set_effect_sound_volume(setting_scene->effect_sound->Drag(mouse_x, mouse_y));
        }
    }

    return GAME_SETTING;
}

int
GameWindow::process_event_select_scene()
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
            select_scene->map_selected(mouse_x, mouse_y);
            set_map(game_map);

            if(select_scene->LabelSelected(mouse_x, mouse_y) == GAME_BACK)
            {
                return back_scene;
            }
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
                player_1_menu->GainHolyWater(1);
            }
            player_1_holy_water_counter = (player_1_holy_water_counter + 1) % holy_water_gain_speed;

            if(player_2_holy_water_counter == 0)
            {
                player_2_menu->GainHolyWater(1);
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
            Minion* m = NULL;
            int new_minion = player_1_menu->MinionSummon(hotkey_1);

            if(new_minion == -1)
            {
                cout << "Player 1 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, red_team,
                              player_1_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_1_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Red_Team_Minion_Set.push_back(m);

                cout << "Player 1 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_N) // player 1 army 2 card hot key
        {
            Minion* m = NULL;
            int new_minion = player_1_menu->MinionSummon(hotkey_2);

            if(new_minion == -1)
            {
                cout << "Player 1 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, red_team,
                              player_1_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_1_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Red_Team_Minion_Set.push_back(m);

                cout << "Player 1 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_M) // player 1 army 3 card hot key
        {
            Minion* m = NULL;
            int new_minion = player_1_menu->MinionSummon(hotkey_3);

            if(new_minion == -1)
            {
                cout << "Player 1 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, red_team,
                              player_1_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_1_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Red_Team_Minion_Set.push_back(m);

                cout << "Player 1 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_G) // player 1 army 4 card hot key
        {
            Minion* m = NULL;
            int new_minion = player_1_menu->MinionSummon(hotkey_4);

            if(new_minion == -1)
            {
                cout << "Player 1 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, red_team,
                              player_1_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_1_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Red_Team_Minion_Set.push_back(m);

                cout << "Player 1 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
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
            Minion* m = NULL;
            int new_minion = player_2_menu->MinionSummon(hotkey_1);

            if(new_minion == -1)
            {
                cout << "Player 2 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, blue_team,
                              player_2_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_2_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Blue_Team_Minion_Set.push_back(m);

                cout << "Player 2 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_2) // player 2 army 2 card hot key
        {
            Minion* m = NULL;
            int new_minion = player_2_menu->MinionSummon(hotkey_2);

            if(new_minion == -1)
            {
                cout << "Player 2 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, blue_team,
                              player_2_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_2_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Blue_Team_Minion_Set.push_back(m);

                cout << "Player 2 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_3) // player 2 army 3 card hot key
        {
            Minion* m = NULL;
            int new_minion = player_2_menu->MinionSummon(hotkey_3);

            if(new_minion == -1)
            {
                cout << "Player 2 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, blue_team,
                              player_2_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_2_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Blue_Team_Minion_Set.push_back(m);

                cout << "Player 2 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
        }
        else if(event.keyboard.keycode == ALLEGRO_KEY_PAD_4) // player 2 army 4 card hot key
        {
            Minion* m = NULL;
            int new_minion = player_2_menu->MinionSummon(hotkey_4);

            if(new_minion == -1)
            {
                cout << "Player 2 cannot create the minion because of lacking of the holy water.\n";
            }
            else
            {
                m = create_minion(new_minion, blue_team,
                              player_2_arena_field_control_pos_x + player_arena_field_control_grid_width/2,
                              player_2_arena_field_control_pos_y + player_arena_field_control_grid_height/2);
                Blue_Team_Minion_Set.push_back(m);

                cout << "Player 2 consumes " << m->getCost()
                     << " point(s) of holy water to create a(n) " <<  m->getName()
                     << " at position (" << m->getAttackX() << "," << m->getAttackY() << ").\n";
            }
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
GameWindow::process_event_pause_scene()
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
GameWindow::process_event_result_scene()
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
GameWindow::process_event_exit_scene()
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
