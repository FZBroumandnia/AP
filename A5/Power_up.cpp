#include "Power_up.h"

Power_up::Power_up(time_t app_t, int in_screen_duration, Rectangle _rec) : rec(_rec)
{
    appearing_t = app_t;
    screen_time_duration = in_screen_duration;
    rec.h = rec.w = WINDOW_SIZE / 15;
    possession_duration = POWER_UP_POSSESSION_DURATION;
    if (rand() % 2)
        type = shot_spead_up;
    else
        type = shield;
}

void Power_up::draw(Window *win)
{
    if (!earned)
    {
        if (type == shield)
            win->draw_img(GIFT1_PIC, rec, NULL_RECT, (0, 0), false, false);
        else
            win->draw_img(GIFT2_PIC, rec, NULL_RECT, (0, 0), false, false);
    }
}

bool Power_up::time_to_disapppear(time_t now)
{
    if (difftime(now, appearing_t) > screen_time_duration)
        return true;

    return false;
}

bool Power_up::time_to_lose(time_t now)
{
    if (difftime(now, earning_t) > possession_duration)
        return true;

    return false;
}
void Power_up::is_earned()
{
    earned = true;
    earning_t = time(0);
};