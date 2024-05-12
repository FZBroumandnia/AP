#ifndef DYNAMIC_ENEMY_H
#define DYNAMIC_ENEMY_H
#include "rsdl.hpp"
#include "Things.h"

class Dynamic_enemy : public Things
{
public:
    Dynamic_enemy(Rectangle _rec, Game *_game, int _col_idx);
    void update(int game_col);

private:
    int vx;
};
#endif
