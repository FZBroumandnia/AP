#include "rsdl.hpp"
#include "Bullet.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>


using namespace std;

Bullet::Bullet(Rectangle _rec, int _vy, int _ay) : rec(_rec)
{
    vy = _vy;
    ay = _ay;
};

void Bullet::update(int _vy)
{
    vy= _vy;
    rec.y += vy;
    center = {rec.x + rec.w / 2, rec.y + rec.h / 2};
    vy += ay;
}

void Bullet::draw(Window *win, string img_add)
{
    win->draw_img(img_add, rec, NULL_RECT, 0, false, false);
}

bool Bullet::hit_thing(Rectangle thing_rect)
{
    if (thing_rect.x <= center.x && center.x <= thing_rect.x + thing_rect.w &&
        thing_rect.y <= center.y && center.y <= thing_rect.y + thing_rect.h)
        return true;
    return false;
}

bool Bullet::bullet_out_page()
{
    int y = rec.y;
    if (y > WINDOW_SIZE || y < 0)
        return true;
    return false;
}