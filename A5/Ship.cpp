#include "Ship.h"

void Ship::update()
{
    rec.y += vy;
    rec.x += vx;
    center = {rec.x + rec.w / 2, rec.y + rec.h / 2};

    if (has_shot_spead_up())
        update_shots(2 * SHIP_B_VY);
    else
        update_shots(SHIP_B_VY);

    handle_touch_h_wall();
    handle_touch_v_wall();
    check_lose_power_up();
}

void Ship::handle_key_press(char key)
{
    switch (key)
    {
    case 'd':
        vx = 10;
        break;
    case 'a':
        vx = -10;
        break;
    case 'w':
        vy = -10;
        break;
    case 's':
        vy = 10;
        break;
    case ' ':
        make_new_bullet(SHIP_B_VY, SHIP_B_AY);
        break;
    }
}

void Ship::handle_key_release(char key)
{
    switch (key)
    {
    case 'd':
        if (vx > 0)
            vx = 0;
        break;
    case 'a':
        if (vx < 0)
            vx = 0;
        break;
    case 'w':
        if (vy < 0)
            vy = 0;
        break;
    case 's':
        if (vy > 0)
            vy = 0;
        break;
    }
}
void Ship::set_random_position()
{
    int win_size = WINDOW_SIZE;
    rec.x = rand() % (win_size - rec.w);
    rec.y = WINDOW_SIZE - rec.h;
}

void Ship::handle_touch_h_wall()
{
    if (rec.y + rec.h >= WINDOW_SIZE)
    {
        rec.y = WINDOW_SIZE - rec.h;
        vy = 0;
    }
    if (rec.y <= 0)
    {
        rec.y = 0;
        vy = 0;
    }
}

void Ship::handle_touch_v_wall()
{
    if (rec.x + rec.w >= WINDOW_SIZE)
    {
        rec.x = WINDOW_SIZE - rec.w;
        vx = 0;
    }

    if (rec.x <= 0)
    {
        rec.x = 0;
        vx = 0;
    }
}

void Ship::draw(Window *win, string img_add)
{
    if (!killed)
    {
        if (!has_shield() && !has_shot_spead_up())
            win->draw_img(img_add, rec, NULL_RECT, 0, false, false);
        else if (has_shield())
            win->draw_img(SHIELD_BOY_PIC, rec, NULL_RECT, 0, false, false);
        else
            win->draw_img(SPEED_BOY_PIC, rec, NULL_RECT, 0, false, false);
    }
    for (int i = 0; i < bullet_vec.size(); i++)
        bullet_vec[i]->draw(win, MUSHROOM_PIC);
}

bool Ship::has_shield()
{
    if (power_up && power_up->get_type() == shield)
        return true;

    return false;
}
bool Ship::has_shot_spead_up()
{
    if (power_up && power_up->get_type() == shot_spead_up)
        return true;
    return false;
}

void Ship::check_earn_power_up(Power_up *_power_up)
{
    vector<Point> vertexes = make_vertex_vector();
    for (Point v : vertexes)
    {
        if (hit_rectangle_point(_power_up->get_rec(), v) && !_power_up->get_earned())
        {
            power_up = _power_up;
            power_up->is_earned();
            break;
        }
    }
}

void Ship::lose_power_up()
{
    power_up = NULL;
}

void Ship::check_lose_power_up()
{
    if (power_up && power_up->time_to_lose(time(0)))
        lose_power_up();
}