#include "rsdl.hpp"
#include "Bullet.h"
#include "Struct.hpp"
#include "Things.h"
#include "Dynamic_enemy.h"
#include "Ship.h"
#include "Ceasefire.h"
#include "Game.h"
#include "Power_up.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <sys/time.h>

using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    Game game;
    game.run(argv[1]);
}