#include "Minion.h"

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

// set counter frequency of drawing moving animation
const int draw_frequency = 10;

Minion::Minion(int posx = 0, int posy = 0, int team = red_team)
{
    this->team = team;

    // default direction
    if (this->team = red_team)
        cur_direction = RIGHT;
    else if (this->team = blue_team)
        cur_direction = LEFT;

    attack_circle = new Circle(posx, posy, 30);
    detect_circle = new Circle(posx, posy, 50);
    self_circle = new Circle(posx, posy, 5);
    // attack_circle and detect_circle and self_circle should be overrode

    // dir_sprite should be overrode

    // name should be overrode
    strncpy(name, "Default", 30);

    is_attack = false;
    cur_sprite = 0;
    counter = 0;
}

Minion::~Minion()
{
    for(unsigned int i=0; i<moveImg.size(); i++)
    {
        ALLEGRO_BITMAP* img = moveImg[i];

        moveImg.erase(moveImg.begin() + i);

        i--;
        al_destroy_bitmap(img);
    }
    moveImg.clear();

    delete attack_circle;
    delete detect_circle;
    delete self_circle;
}

bool
Minion::OnTheBridge(double pos_x, double pos_y)
{
    double bridge_x1 = (double)(window_width/2 - BRIDGE_WIDTH/2);
    double bridge_x2 = (double)(window_width/2 + BRIDGE_WIDTH/2);

    double upper_bridge_y1 = (double)(scoreboard_height + UPPER_BRIDGE_Y - BRIDGE_HEIGHT/2);
    double upper_bridge_y2 = (double)(scoreboard_height + UPPER_BRIDGE_Y + BRIDGE_HEIGHT/2);
    double lower_bridge_y1 = (double)(scoreboard_height + LOWER_BRIDGE_Y - BRIDGE_HEIGHT/2);
    double lower_bridge_y2 = (double)(scoreboard_height + LOWER_BRIDGE_Y + BRIDGE_HEIGHT/2);

    if(pos_x >= bridge_x1 && pos_x <= bridge_x2 && pos_y >= upper_bridge_y1 && pos_y <= upper_bridge_y2)
    {
        return true;
    }
    else if(pos_x >= bridge_x1 && pos_x <= bridge_x2 && pos_y >= lower_bridge_y1 && pos_y <= lower_bridge_y2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void
Minion::Draw()
{
    int w, h;
    int offset = 0;

    // calculate the number of pictures before current direction
    for(int i=0; i<cur_direction; i++)
        offset += dir_sprite[i];

    if(!moveImg[offset + cur_sprite])
        return;

    // get height and width of sprite bitmap
    w = al_get_bitmap_width(moveImg[offset + cur_sprite]);
    h = al_get_bitmap_height(moveImg[offset + cur_sprite]);

    // draw bitmap align grid edge
    al_draw_bitmap(moveImg[offset + cur_sprite], attack_circle->x - w/2, attack_circle->y - (h - grid_height/2), 0);

    //al_draw_filled_circle(circle->x, circle->y, circle->r, al_map_rgba(196, 79, 79, 200));

    //cout << "(" << attack_circle->x << "," << attack_circle->y << ")" << endl;
    //cout << "direction : " << cur_direction << endl;
}

void
Minion::find_way() // to find the values of unit_heading_x and unit_heading_y
{
    double path_x, path_y, path_length;

    if (type == AIR_UNIT)
        path_stage = HEADING_TO_TOWER;

    switch (getPathStage())
    {
        case HEADING_TO_BRIDGE:
            int heading_bridge;

            if (team == red_team)
                path_x = (double) (window_width / 2 - BRIDGE_WIDTH / 2 - attack_circle->x);
            else if (team == blue_team)
                path_x = (double) (window_width / 2 + BRIDGE_WIDTH / 2 - attack_circle->x);

            heading_bridge = (abs(scoreboard_height + UPPER_BRIDGE_Y - attack_circle->y) < abs(scoreboard_height + LOWER_BRIDGE_Y - attack_circle->y))
                                ? UPPER_BRIDGE : LOWER_BRIDGE;

            if (heading_bridge == UPPER_BRIDGE)
                path_y = (double) (scoreboard_height + UPPER_BRIDGE_Y - attack_circle->y);
            else if (heading_bridge == LOWER_BRIDGE)
                path_y = (double) (scoreboard_height + LOWER_BRIDGE_Y - attack_circle->y);

            path_length = sqrt(path_x * path_x + path_y * path_y);

            unit_heading_x = (double) path_x / path_length;
            unit_heading_y = (double) path_y / path_length;
            break;
        case PASSING_BRIDGE:
            if (team == red_team)
                unit_heading_x = 1;
            else if (team == blue_team)
                unit_heading_x = -1;
            unit_heading_y = 0;
            break;
        case HEADING_TO_TOWER:
            path_x = (double) closest_tower_x - attack_circle->x;
            path_y = (double) closest_tower_y - attack_circle->y;
            path_length = sqrt(path_x * path_x + path_y * path_y);

            unit_heading_x = (double) path_x / path_length;
            unit_heading_y = (double) path_y / path_length;
            break;
        default:
            cout << "Error occurs !!" << endl;
    }

    if (unit_heading_x > 0)
        cur_direction = RIGHT;
    else if (unit_heading_x < 0)
        cur_direction = LEFT;

    if (unit_heading_y != 0)
    {
        double diff = (double) abs(unit_heading_x) - abs(unit_heading_y);

        if (diff < 0)
        {
            if (unit_heading_y > 0)
                cur_direction = UP;
            else
                cur_direction = DOWN;
        }
    }
}

void
Minion:: findClosestTower(int tower_x, int tower_y)
{
    closest_tower_x = tower_x;
    closest_tower_y = tower_y;
}

bool
Minion::Substract_HP(int harm)
{
    HealthPoint -= harm;

    return (HealthPoint <= 0);
}

void
Minion:: Move()
{
    static int prev_direction = LEFT;

    counter = (counter + 1) % draw_frequency;

    if (!getIsAttack())
    {
        prev_direction = cur_direction;
        if (counter == 0)
            cur_sprite = (cur_sprite + 1) % dir_sprite[cur_direction];
        // attack sprite++
    }

    if (prev_direction != cur_direction)
        cur_sprite = 0;

    attack_circle->x += speed * unit_heading_x;
    attack_circle->y += speed * unit_heading_y;

    detect_circle->x += speed * unit_heading_x;
    detect_circle->y += speed * unit_heading_y;

    if(type == GROUND_UNIT && path_stage == HEADING_TO_BRIDGE && OnTheBridge(attack_circle->x, attack_circle->y))
    {
        path_stage = PASSING_BRIDGE;
    }
    else if(type == GROUND_UNIT && path_stage == PASSING_BRIDGE && !OnTheBridge(attack_circle->x, attack_circle->y))
    {
        path_stage = HEADING_TO_TOWER;
    }
}
void
Minion::LoadAnimation()
{
    char buffer[50];

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<dir_sprite[i]; j++)
        {
            ALLEGRO_BITMAP *img;
            sprintf(buffer, "./image/Minion/%s/%s_%d.png", name, direction_name[i], j+1);

            img = al_load_bitmap(buffer);
            if (img)
                moveImg.push_back(img);
            else
                cout << "LoadAnimation failed!" << endl;
        }
    }
}

bool
Minion::DetectAttack(Minion *minion)
{
    Attack *attack;
    RangeAttack *rangeattack;
    is_attack = false;

    if(Circle::isOverlap(this->detect_circle, minion->getSelfCircle()))
    {
        this->detect_set.push_back(minion);
    }
    else if(Circle::isOverlap(this->attack_circle, minion->getSelfCircle()))
    {
        if(attack_counter == 0)
        {
            if(attack_type == MELEE)
            {
                attack = new Attack(
                    this->attack_circle,
                    minion->getSelfCircle(),
                    this->attack_harm_point,
                    this->attack_velocity,
                    this->attackImg
                );
                this->attack_set.push_back(attack);
            }
            else if(attack_type == RANGER)
            {
                rangeattack = new RangeAttack(
                    this->attack_circle,
                    minion->getSelfCircle(),
                    this->attack_harm_point,
                    this->attack_velocity,
                    this->attackImg
                );
                this->rangeattack_set.push_back(rangeattack);
            }

            is_attack = true;
        }
    }
    return is_attack;
}

bool
Minion::TriggerAttack(Minion* minion)
{
    bool destroyed = false;

    if(attack_type == MELEE)
    {
        for(unsigned int i = 0; i < this->attack_set.size(); i++)
        {
            if(Circle::isOverlap(attack_set[i]->getCircle(), minion->getSelfCircle()))
            destroyed = minion->Substract_HP(attack_harm_point);

            this->attack_set.erase(this->attack_set.begin() + i);
            delete(this->attack_set[i]);
            if(destroyed)
                break;
        }
    }
    else if(attack_type == RANGER)
    {
        for(unsigned int i = 0; i < this->rangeattack_set.size(); i++)
        {
            if(Circle::isOverlap(rangeattack_set[i]->getAttackCircle(), minion->getSelfCircle()))
            destroyed = minion->Substract_HP(attack_harm_point);

            this->rangeattack_set.erase(this->rangeattack_set.begin() + i);
            delete(this->rangeattack_set[i]);
            if(destroyed)
                break;
        }
    }

    return destroyed;
}

void
Minion::UpdateAttack()
{
    if(attack_type == MELEE)
    {
        for(unsigned int i=0; i < this->attack_set.size(); i++)
        {
            if(!Circle::isOverlap(attack_set[i]->getSelfCircle(), this->attack_circle))
            {
                Attack *attack = this->attack_set[i];

                this->attack_set.erase(this->attack_set.begin() + i);
                i--;
                delete attack;
            }
        }
    }
    else if(attack_type == RANGER)
    {
        for(unsigned int i=0; i < this->rangeattack_set.size(); i++)
        {
            if(!Circle::isOverlap(rangeattack_set[i]->getSelfCircle(), this->attack_circle))
            {
                Attack *attack = this->rangeattack_set[i];

                this->attack_set.erase(this->rangeattack_set.begin() + i);
                i--;
                delete attack;
            }
        }
    }
}
