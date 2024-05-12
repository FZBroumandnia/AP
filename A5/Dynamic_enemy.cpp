#include "Dynamic_enemy.h"

Dynamic_enemy::Dynamic_enemy(Rectangle _rec, Game *_game, int _col_idx) : Things(_rec, _game, _col_idx)
{
    vx = rand() % (5 + 1 - 2) + 2;
};

void Dynamic_enemy::update(int game_col)
{
    if (rec.x + rec.w > WINDOW_SIZE || rec.x < 0)
        vx = -vx;
    rec.x += vx;
    center = {rec.x + rec.w / 2, rec.y + rec.h / 2};
    col_idx = (rec.x + rec.w) / (WINDOW_SIZE / game_col);
}