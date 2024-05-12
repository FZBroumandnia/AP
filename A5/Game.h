#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <sys/time.h>

#include "Ceasefire.h"
#include "Dynamic_enemy.h"
#include "Ship.h"
#include "Power_up.h"

using namespace std;

class Game
{
public:
    Game();
    void run(const char *file);

    void handle_hits();

    void if_hship_die_you_die();
    bool all_enemies_killed();

    void clear_things_vector();
    void clear_bullet_vector_game();

    void set_mode(ifstream &map_file);
    void fill_out_vector(ifstream &map_file, int row, int col);
    void set_row_col(ifstream &input_file);

    void process_bullet_shooting(int time_x);
    void make_power_up();
    void set_game(ifstream &input_file);

    vector<string> make_game_map(ifstream &input_file, int row);
    Things_positions make_enemy_vector(ifstream &input_file, int row, int col);

private:
    void process_events(int time_x, time_t game_start_time);
    void draw_screen();
    void update_objects();

    bool game_running;
    Ship ship;
    vector<Things> hostage_ships;
    vector<Things> static_enemies;
    vector<Dynamic_enemy> dynamic_enemies;
    Window win;

    int cols;
    int rows;
    int stages_num;
    int mode;
    Ceasefire_col ceasefire_cols;
    vector<Power_up *> power_ups_vec;
};

#endif