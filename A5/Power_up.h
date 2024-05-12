#ifndef POWER_UP_H
#define POWER_UP_H

#include "rsdl.hpp"
#include "Struct.hpp"
#include <ctime>

class Power_up
{
public:
    Power_up(time_t app_t, int in_screen_duration, Rectangle _rec);

    Rectangle get_rec() { return rec; };
    int get_type() {return type;}
    bool get_earned() { return earned; };

    void draw(Window *win);
    bool time_to_disapppear(time_t now);
    bool time_to_lose(time_t now);
    void is_earned();
    

private:
    bool earned = false;
    int type;
    Rectangle rec;
    time_t appearing_t;
    time_t earning_t;
    int screen_time_duration;
    int possession_duration;
};

#endif