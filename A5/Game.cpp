#include "Game.h"

vector<string> Game::make_game_map(ifstream &input_file, int row)
{
    vector<string> game_map;
    string line;
    for (int i = 0; i < row; i++)
    {
        getline(input_file, line);
        if (line == "---")
            getline(input_file, line);
        game_map.push_back(line);
    }
    return game_map;
}

Things_positions Game::make_enemy_vector(ifstream &input_file, int row, int col)
{
    vector<string> game_map = make_game_map(input_file, row);
    int row_len, col_len;
    row_len = WINDOW_SIZE / row;
    col_len = WINDOW_SIZE / col;

    vector<Position> static_enemies_p;
    vector<Position> dynamic_enemies_p;
    vector<Position> hostage_ships;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (game_map[i][j] == HOSTAGE_SHIP)
                hostage_ships.push_back({j * col_len, i * row_len, j});
            if (game_map[i][j] == STATIC_ENEMY)
                static_enemies_p.push_back({j * col_len, i * row_len, j});
            if (game_map[i][j] == DYNAMIC_ENEMY)
                dynamic_enemies_p.push_back({j * col_len, i * row_len, j});
        }
    }
    return {hostage_ships, static_enemies_p, dynamic_enemies_p};
}

void Game::clear_things_vector()
{
    static_enemies.clear();
    dynamic_enemies.clear();
    hostage_ships.clear();
    power_ups_vec.clear();
}

void Game::clear_bullet_vector_game()
{
    ship.clear_bull_vec();
    for (int i = 0; i < dynamic_enemies.size(); i++)
        dynamic_enemies[i].clear_bull_vec();
    for (int i = 0; i < static_enemies.size(); i++)
        static_enemies[i].clear_bull_vec();
}

void Game::set_mode(ifstream &map_file)
{
    string line;
    getline(map_file, line);
    if (line == "Easy")
        mode = EASY;
    else if (line == "Medium")
        mode = MEDIUM;
    else if (line == "Hard")
        mode = HARD;
}

void Game::if_hship_die_you_die()
{
    for (Things hship : hostage_ships)
        ship.kill_teammate(hship);
}

void Game::handle_hits()
{
    for (int i = 0; i < static_enemies.size(); i++)
    {
        ship.kill_sb(&static_enemies[i]);
        ship.collision(&static_enemies[i]);
        if (!ship.has_shield())
            static_enemies[i].kill_sb(&ship);
    }

    for (int i = 0; i < dynamic_enemies.size(); i++)
    {
        ship.kill_sb(&dynamic_enemies[i]);
        ship.collision(&dynamic_enemies[i]);
        if (!ship.has_shield())
            dynamic_enemies[i].kill_sb(&ship);
    }

    for (int i = 0; i < hostage_ships.size(); i++)
    {
        ship.kill_sb(&hostage_ships[i]);
        ship.collision(&hostage_ships[i]);
    }
    for (int i = 0; i < power_ups_vec.size(); i++)
        ship.check_earn_power_up(power_ups_vec[i]);
}

Game::Game() : win(WINDOW_SIZE, WINDOW_SIZE + WINDOW_SIZE / 10, "STARWARS"), ship(Point(0, 0), Point(SHIP_W, SHIP_HE), this), ceasefire_cols(0, 0)
{
}

void Game::set_game(ifstream &input_file)
{
    clear_bullet_vector_game();
    clear_things_vector();
    fill_out_vector(input_file, rows, cols);
    set_mode(input_file);
    ship.lose_power_up();
    ship.set_random_position();
    game_running = true;
    ceasefire_cols.set(cols, mode);
}

void Game::set_row_col(ifstream &input_file)
{
    string line;
    int row, col, stage_num;
    getline(input_file, line, DELIMITER);
    row = stoi(line);
    getline(input_file, line);
    col = stoi(line);

    getline(input_file, line);
    stage_num = stoi(line);
    cols = col;
    rows = row;
    stages_num = stage_num;
}

void Game::fill_out_vector(ifstream &map_file, int row, int col)
{
    Things_positions thp = make_enemy_vector(map_file, row, col);
    for (Position p : thp.static_enemy)
    {
        Things static_enemy(Rectangle(Point(p.x, p.y), Point(p.x + S_ENEMY_W, p.y + S_ENEMY_H)), this, p.col_idx);
        static_enemies.push_back(static_enemy);
    }
    for (Position p : thp.dynamic_enemy)
    {
        Dynamic_enemy dynamic_enemy(Rectangle(Point(p.x, p.y), Point(p.x + D_ENEMY_W, p.y + D_ENEMY_H)), this, p.col_idx);
        dynamic_enemies.push_back(dynamic_enemy);
    }
    for (Position p : thp.hostage_ships)
    {
        Things hostage_ship(Rectangle(Point(p.x, p.y), Point(p.x + H_SHIP_W, p.y + H_SHIP_H)), this, p.col_idx);
        hostage_ships.push_back(hostage_ship);
    }
}

bool Game::all_enemies_killed()
{
    for (int i = 0; i < static_enemies.size(); i++)
    {
        if (!static_enemies[i].get_killed())
            return false;
    }
    for (int i = 0; i < dynamic_enemies.size(); i++)
    {
        if (!dynamic_enemies[i].get_killed())
            return false;
    }
    return true;
}

void Game::run(const char *file)
{
    game_running = true;
    int time_scope = 0;

    ifstream input_file;
    input_file.open(file);
    set_row_col(input_file);

    for (int i = 0; i < stages_num; i++)
    {
        set_game(input_file);
        time_t game_start_time = time(0);

        while (!all_enemies_killed() && game_running)
        {
            process_events(time_scope, game_start_time);
            update_objects();
            draw_screen();
            delay(15);
            time_scope++;
            if (time_scope == 1000)
                time_scope = 0;
        }
        if (!game_running)
            break;
        delay(700);
    }
    // delay(700);
}

void Game::process_bullet_shooting(int time_scope)
{
    if (!(time_scope % 200))
    {
        ceasefire_cols.make_ceasefire_col();
        for (int i = 0; i < dynamic_enemies.size(); i++)
            dynamic_enemies[i].check_condition_for_make_bullet(ENEMY_B_VY, ENEMY_B_AY, ceasefire_cols.get_ceasefire_col_bool());

        for (int i = 0; i < static_enemies.size(); i++)
            static_enemies[i].check_condition_for_make_bullet(ENEMY_B_VY, ENEMY_B_AY, ceasefire_cols.get_ceasefire_col_bool());
    }
}

void Game::process_events(int time_scope, time_t game_start_time)
{
    while (win.has_pending_event())
    {
        Event event = win.poll_for_event();
        switch (event.get_type())
        {
        case Event::QUIT:
            game_running = false;
            break;
        case Event::KEY_PRESS:
            ship.handle_key_press(event.get_pressed_key());
            break;
        case Event::KEY_RELEASE:
            ship.handle_key_release(event.get_pressed_key());
            break;
        }
    }

    time_t now = time(0);
    if (difftime(now, game_start_time) > START_DELAY)
        process_bullet_shooting(time_scope);
    make_power_up();
}

void Game::make_power_up()
{
    time_t now = time(0);
    if (rand() % 2)
    {
        for (int i = 0; i < static_enemies.size(); i++)
        {
            if (static_enemies[i].get_killed())
            {
                Power_up *new_power_up = new Power_up(now, POWER_UP_DURATION, static_enemies[i].get_rec());
                power_ups_vec.push_back(new_power_up);
                static_enemies.erase(static_enemies.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < dynamic_enemies.size(); i++)
        {
            if (dynamic_enemies[i].get_killed())
            {
                Power_up *new_power_up = new Power_up(now, POWER_UP_DURATION, dynamic_enemies[i].get_rec());
                power_ups_vec.push_back(new_power_up);
                dynamic_enemies.erase(dynamic_enemies.begin() + i);
                i--;
            }
        }
    }
}

void Game::draw_screen()
{
    win.clear();
    win.draw_img(MAIN_BG, NULL_RECT, NULL_RECT, 0, false, false);

    if (ship.get_killed())
        win.draw_img(GAME_OVER_BG, NULL_RECT, NULL_RECT, 0, false, false);

    else
    {
        ship.draw(&win, BOY_PIC);
        for (Things enemy : static_enemies)
            enemy.draw(&win, CACTUS_PIC);
        for (Dynamic_enemy enemy : dynamic_enemies)
            enemy.draw(&win, DINA_PIC);
        for (Things hship : hostage_ships)
            hship.draw(&win, PRINCESS_PIC);
        for (Power_up *pu : power_ups_vec)
            pu->draw(&win);
    }
    win.update_screen();
}

void Game::update_objects()
{
    ship.update();
    for (int i = 0; i < dynamic_enemies.size(); i++)
    {
        dynamic_enemies[i].update(cols);
        dynamic_enemies[i].update_shots(ENEMY_B_VY);
    }
    for (int i = 0; i < static_enemies.size(); i++)
        static_enemies[i].update_shots(ENEMY_B_VY);
    handle_hits();

    for (Things hship : hostage_ships)
        ship.kill_teammate(hship);

    for (int i = 0; i < power_ups_vec.size(); i++)
    {
        if (power_ups_vec[i]->time_to_disapppear(time(0)))
        {
            Power_up *p_ptr = power_ups_vec[i];
            power_ups_vec.erase(power_ups_vec.begin() + i);
            if (!power_ups_vec[i]->get_earned())
                delete p_ptr;
            i--;
        }
    }
}