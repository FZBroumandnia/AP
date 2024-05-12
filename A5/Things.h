#ifndef THINGS_HPP
#define THINGS_HPP

#include "rsdl.hpp"
#include "Struct.hpp"
#include "Bullet.h"
class Game;

class Things
{
public:
    Things(Rectangle _rec, Game *_game, int _col_idx);

    bool get_killed() { return killed; };

    void make_new_bullet(int vy, int ay);
    void draw(Window *win, string img_add);
    void update_shots(int _vy);
    void delete_bullet(int i);

    Rectangle get_rec() { return rec; };

    void clear_bull_vec();
    void kill_sb(Things *other);
    void kill_teammate(Things other);
    bool hit_rectangle_point(Rectangle rect, Point point);
    vector<Point> make_vertex_vector();
    void collision(Things *other);
    void check_condition_for_make_bullet(int vy, int ay, vector<bool> ceasefire_col_bool);

private:
    Game *game;

protected:
    Position center;
    bool killed = false;
    int col_idx;
    Rectangle rec;
    vector<Bullet *> bullet_vec;
};
#endif
