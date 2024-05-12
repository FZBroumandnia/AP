#ifndef STRUCT_HPP
#define STRUCT_HPP

#include <iostream>
#include "rsdl.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>

using namespace std;

const double START_DELAY = 0.3;
const int POWER_UP_DURATION = 5;
const int POWER_UP_POSSESSION_DURATION = 8;
const double WINDOW_SIZE = 750;

const string BOY_PIC = "photo/boyy.png";
const string SHIELD_BOY_PIC = "photo/shieldboy.png";
const string SPEED_BOY_PIC = "photo/speedboy.png";
const string FIRE_PIC = "photo/firee.png";
const string MUSHROOM_PIC = "photo/mushroomm.png";
const string PRINCESS_PIC = "photo/lpic.png";
const string CACTUS_PIC = "photo/Cactuss.png";
const string DINA_PIC = "photo/Dinaa.png";
const string GIFT1_PIC = "photo/gift1.png";
const string GIFT2_PIC = "photo/gift2.png";
const string GAME_OVER_BG = "photo/NEO_GO.jpg";
const string MAIN_BG = "photo/bgwcs2.jpg";

const double SHIP_W = WINDOW_SIZE / 10;
const double SHIP_HE = WINDOW_SIZE / 5.5;
const double S_ENEMY_W = WINDOW_SIZE / 13.3;
const double S_ENEMY_H = WINDOW_SIZE / 10;
const double D_ENEMY_W = WINDOW_SIZE / 7;
const double D_ENEMY_H = WINDOW_SIZE / 7;
const double H_SHIP_W = WINDOW_SIZE / 6;
const double H_SHIP_H = WINDOW_SIZE / 6;
const double BULLET_W = WINDOW_SIZE / 25;
const double BULLET_H = WINDOW_SIZE / 20;

const char DELIMITER = ' ';

const char HOSTAGE_SHIP = 'S';
const char DYNAMIC_ENEMY = 'M';
const char STATIC_ENEMY = 'E';

const int SHIP_B_VY = -13;
const int SHIP_B_AY = 0;

const int ENEMY_B_VY = 3;
const int ENEMY_B_AY = 0;

enum power_up_types
{
    shot_spead_up,
    shield,
};

enum game_modes
{
    EASY = 3,
    MEDIUM = 2,
    HARD = 1,
};

struct Position
{
    int x;
    int y;
    int col_idx;
};

struct Things_positions
{
    vector<Position> hostage_ships;
    vector<Position> static_enemy;
    vector<Position> dynamic_enemy;
};

#endif