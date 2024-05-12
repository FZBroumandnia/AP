#include "Things.h"

Things::Things(Rectangle _rec, Game *_game, int _col_idx) : rec(_rec), game(_game)
{
    col_idx = _col_idx;
    center = {rec.x + rec.w / 2, rec.y + rec.h / 2};
};
void Things::kill_sb(Things *other)
{
    for (int j = 0; j < bullet_vec.size(); j++)
    {
        if (bullet_vec[j]->hit_thing(other->rec) && !other->killed)
        {
            other->killed = true;
            delete_bullet(j);
            break;
        }
    }
}

void Things::kill_teammate(Things other)
{
    if (other.killed)
        killed = true;
}

bool Things::hit_rectangle_point(Rectangle rect, Point p)
{
    if (rect.x <= p.x && p.x <= rect.x + rect.w &&
        rect.y <= p.y && p.y <= rect.y + rect.h)
        return true;
    return false;
}

vector<Point> Things::make_vertex_vector()
{
    return {{rec.x, rec.y}, {rec.x + rec.w, rec.y}, {rec.x, rec.y + rec.h}, {rec.x + rec.w, rec.y + rec.h}};
}

void Things::collision(Things *other)
{
    vector<Point> vertexes = make_vertex_vector();
    for (Point v : vertexes)
    {
        if (hit_rectangle_point(other->rec, v) && !other->killed)
        {
            killed = true;
            break;
        }
    }
}
void Things::check_condition_for_make_bullet(int vy, int ay, vector<bool> ceasefire_col_bool)
{
    if (!killed && !ceasefire_col_bool[col_idx])
        make_new_bullet(vy, ay);
}

void Things::make_new_bullet(int vy, int ay)
{
    Bullet *new_bull = new Bullet(Rectangle(center.x - WINDOW_SIZE / 50, rec.y, BULLET_W, BULLET_H), vy, ay);
    bullet_vec.push_back(new_bull);
}

void Things::draw(Window *win, string img_add)
{
    if (!killed)
        win->draw_img(img_add, rec, NULL_RECT, 0, false, false);
    for (int i = 0; i < bullet_vec.size(); i++)
        bullet_vec[i]->draw(win, FIRE_PIC);
}
void Things::delete_bullet(int i)
{
    Bullet *b_ptr = bullet_vec[i];
    bullet_vec.erase(bullet_vec.begin() + i);
    delete b_ptr;
};

void Things::clear_bull_vec()
{
    for (int i = 0; i < bullet_vec.size(); i++)
        delete bullet_vec[i];
    bullet_vec.clear();
}

void Things::update_shots(int _vy)
{
    for (int i = 0; i < bullet_vec.size(); i++)
    {
        bullet_vec[i]->update(_vy);
        if (bullet_vec[i]->bullet_out_page())
        {
            delete_bullet(i);
            i--;
        }
    }
}