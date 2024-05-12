#ifndef SHIP_H
#define SHIP_H

#include "rsdl.hpp"
#include "Things.h"
#include "Power_up.h"

class Ship : public Things
{
public:
    Ship(Point _p1, Point _p2, Game *_game) : Things(Rectangle(_p1, _p2), _game, 0){};
    void update();
    void handle_key_press(char key);
    void handle_key_release(char key);
    void set_random_position();
    void draw(Window *win, string img_add);
    bool has_shield();
    bool has_shot_spead_up();
    void check_earn_power_up(Power_up *_power_up);
    void lose_power_up();
    void check_lose_power_up();

private:
    void handle_touch_h_wall();
    void handle_touch_v_wall();
    double vx, vy;
    Power_up *power_up;
};

#endif