#ifndef BULLET_HPP
#define BULLET_HPP

#include "rsdl.hpp"

#include "Struct.hpp"

#include <iostream>
#include <cstdlib>

using namespace std;

class Bullet
{
public:
    Bullet(Rectangle _rec, int _vy, int _ay);
    void update(int _vy);
    void draw(Window *win, string img_add);
    bool hit_thing(Rectangle rect);
    bool bullet_out_page();

private:
    double vy;
    double ay;
    Position center;
    Rectangle rec;
};

#endif
