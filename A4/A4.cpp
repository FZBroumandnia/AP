#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

const char DELIMITER = ' ';

const int HEAVY_PRICE = 3000;
const int PISTOL_PRICE = 400;
const int MAX_MONEY = 10000;
const int INITIAL_MONEY = 1000;
const int INITIAL_HEALTH = 100;
const int LOSER_REWARD = 2400;
const int WINNER_REWARD = 2700;

const int DOES_NOT_EXIST = -1;

const string DONE_MSG = "ok";
const string AFK_MSG = "user not available";
const string NO_WPN_MSG = "weapon not available";
const string AFTER_START_MSG = "fight!";
const string AFTER_START_ERR = "you can't buy weapons anymore";
const string BEFORE_START_ERR = "The game hasn't started yet";
const string SUCCESSFULL_PAYMENT_MSG = "weapon bought successfully";
const string ALREADY_HAVE_MSG = "you already have this weapon";
const string DOES_NOT_HAVE = "attacker doesn't have this gun";

const string DEAD_ATTACKER_MSG = "attacker is dead";
const string DEAD_ATTACKED_MSG = "attacked is dead";
const string TEAMMATE_ERR = "you can't shoot this player";
const string SUCCESSFULL_SHOT_MSG = "nice shot";
const string MONEY_LOSS_ERR = "insufficient money";

const string TRR_LIST_HEADER = "terrorist players:";
const string CNT_LIST_HEADER = "counter-terrorist players:";

const string TRR_WON_MSG = "terrorist won";
const string CNT_WON_MSG = "counter-terrorist won";

struct Weapon
{
    string name;
    int price;
    int health_dec;
    int money_inc;
};
const vector<Weapon> WEAPON_LIST = {{"knife", DOES_NOT_EXIST, 35, 500}, {"pistol", 400, 20, 200}, {"heavy", 3000, 45, 100}};

struct Reward
{
    int terrorist;
    int counter_terrorist;
};

class Player
{
public:
    Player(){};
    Player(string n, string type)
    {
        username = n;
        is_terrorist = (type == "terrorist") ? true : false;
    };

    void set_health() { health = INITIAL_HEALTH; }
    string get_name() { return username; }
    int get_health() { return health; }
    int get_money() { return money; }
    bool get_is_terrorist() { return is_terrorist; }
    bool get_afk() { return afk; }

    void buy(string weapon_name);
    bool have_this_weapon(int idx);
    bool is_better(Player second);
    void attack(int idx, bool is_killed);
    bool being_attacked(int idx);
    bool have_this_weapon(string weapon_name);
    bool sufficient_money(int weapon_idx);

    void go_atk()
    {
        afk = false;
        cout << DONE_MSG << endl;
    }
    void go_afk()
    {
        afk = true;
        cout << DONE_MSG << endl;
    }
    void print_scores()
    {
        cout << username << DELIMITER << kills << DELIMITER << deaths << endl;
    }
    void money_inc(int reward)
    {
        money += reward;
        if (money > MAX_MONEY)
            money = MAX_MONEY;
    }
    void pay_money(int price)
    {
        money = money - price;
    }

private:
    string username;
    bool is_terrorist;
    int health = INITIAL_HEALTH;
    int money = INITIAL_MONEY;
    int kills = 0;
    int deaths = 0;
    bool afk = false;
    bool heavy = false;
    bool knife = true;
    bool pistol = false;
};
typedef vector<Player> Player_list;

struct Status
{
    bool start = false;
    Player_list p_list;
};

bool Player::have_this_weapon(int idx)
{
    if (idx == 0 && knife)
        return true;
    else if (idx == 1 && pistol)
        return true;
    else if (idx == 2 && heavy)
        return true;
    return false;
}

bool Player::is_better(Player second)
{
    if (kills < second.kills)
        return true;
    if (kills == second.kills && deaths > second.deaths)
        return true;
    if (kills == second.kills && deaths == second.deaths && username.compare(second.username) > 0)
        return true;
    return false;
}

bool Player::being_attacked(int idx)
{
    bool is_killed = false;
    health = health - WEAPON_LIST[idx].health_dec;
    if (health <= 0)
    {
        health = 0;
        deaths++;
        heavy = false;
        pistol = false;
        is_killed = true;
    }
    return is_killed;
}

void Player::attack(int idx, bool is_killed)
{
    if (idx == 1)
        pistol = false;
    else if (idx == 2)
        heavy = false;
    if (is_killed)
    {
        kills++;
        money += WEAPON_LIST[idx].money_inc;
    }
}

void Player::buy(string weapon_name)
{
    if (weapon_name == "pistol")
    {
        pay_money(PISTOL_PRICE);
        pistol = true;
    }
    else if (weapon_name == "heavy")
    {
        pay_money(HEAVY_PRICE);
        heavy = true;
    }
}

bool Player::sufficient_money(int weapon_idx)
{
    if (money - WEAPON_LIST[weapon_idx].price < 0)
        return false;
    return true;
}

bool Player::have_this_weapon(string weapon_name)
{
    if (weapon_name == "knife")
        return true;
    if (weapon_name == "pistol" && pistol)
        return true;
    if (weapon_name == "heavy" && heavy)
        return true;
    return false;
}

Player add_user(string name, string type)
{
    Player new_p(name, type);
    cout << "ok" << endl;
    return new_p;
}

Player find_user(string name, vector<Player> p_list)
{
    Player this_one;
    for (int i = 0; i < p_list.size(); i++)
    {
        if (name == p_list[i].get_name())
            this_one = p_list[i];
    }
    return this_one;
}

int find_user_idx(string name, vector<Player> p_list)
{
    for (int i = 0; i < p_list.size(); i++)
    {
        if (name == p_list[i].get_name())
            return i;
    }
    return DOES_NOT_EXIST;
}

int find_weapon_idx(string name)
{
    int idx;
    if (name == WEAPON_LIST[0].name)
        idx = 0;
    else if (name == WEAPON_LIST[1].name)
        idx = 1;
    else if (name == WEAPON_LIST[2].name)
        idx = 2;
    else
        idx = -1;
    return idx;
}

Player buy(string weapon_name, Player player, bool start)
{
    if (start)
        cout << AFTER_START_ERR << endl;
    else if (player.get_afk())
        cout << AFK_MSG << endl;
    else if (find_weapon_idx(weapon_name) == DOES_NOT_EXIST)
        cout << NO_WPN_MSG << endl;
    else if (player.have_this_weapon(weapon_name))
        cout << ALREADY_HAVE_MSG << endl;
    else if (!player.sufficient_money(find_weapon_idx(weapon_name)))
        cout << MONEY_LOSS_ERR << endl;
    else
    {
        player.buy(weapon_name);
        cout << SUCCESSFULL_PAYMENT_MSG << endl;
    }

    return player;
}

Player_list shoot(vector<string> splited_line, Player_list p_list, bool start)
{
    int attacker_idx = find_user_idx(splited_line[1], p_list);
    int attacked_idx = find_user_idx(splited_line[2], p_list);
    string weapon_name = splited_line[3];
    if (!start)
        cout << BEFORE_START_ERR << endl;
    else if (p_list[attacker_idx].get_afk() || p_list[attacked_idx].get_afk())
        cout << AFK_MSG << endl;
    else if (attacker_idx == DOES_NOT_EXIST || attacked_idx == DOES_NOT_EXIST)
        cout << AFK_MSG << endl;
    else if (!p_list[attacker_idx].get_health())
        cout << DEAD_ATTACKER_MSG << endl;
    else if (!p_list[attacked_idx].get_health())
        cout << DEAD_ATTACKED_MSG << endl;
    else if (p_list[attacker_idx].get_is_terrorist() == p_list[attacked_idx].get_is_terrorist())
        cout << TEAMMATE_ERR << endl;
    else if (!p_list[attacker_idx].have_this_weapon(find_weapon_idx(weapon_name)))
        cout << DOES_NOT_HAVE << endl;
    else
    {
        int weapon_idx = find_weapon_idx(weapon_name);
        bool is_killed = p_list[attacked_idx].being_attacked(weapon_idx);
        p_list[attacker_idx].attack(weapon_idx, is_killed);
        cout << SUCCESSFULL_SHOT_MSG << endl;
    }
    return p_list;
}

vector<string> split_line(string line)
{
    stringstream new_line(line);
    string splited_str;
    vector<string> splited_vector;
    while (getline(new_line, splited_str, DELIMITER))
        splited_vector.push_back(splited_str);
    return splited_vector;
}

bool all_printed(vector<bool> printed)
{
    for (int i = 0; i < printed.size(); i++)
    {
        if (!printed[i])
            return false;
    }
    return true;
}

int find_best_player_idx(Player_list p_list, vector<bool> printed)
{
    int best_idx = 0;
    for (int i = 0; i < p_list.size(); i++)
    {
        if (printed[i])
            continue;
        while (printed[best_idx])
            best_idx++;
        if (p_list[best_idx].is_better(p_list[i]))
            best_idx = i;
    }
    return best_idx;
}

void print_each_team_score_board(Player_list p_list)
{
    vector<bool> printed(p_list.size(), false);
    while (!all_printed(printed))
    {
        int best_idx = find_best_player_idx(p_list, printed);
        p_list[best_idx].print_scores();
        printed[best_idx] = true;
    }
}

Player_list make_team_list(Player_list p_list, bool is_terrorist)
{
    Player_list team_list;
    for (int i = 0; i < p_list.size(); i++)
    {
        if ((is_terrorist) ? p_list[i].get_is_terrorist() : !p_list[i].get_is_terrorist())
            team_list.push_back(p_list[i]);
    }
    return team_list;
}

void print_score_board(Player_list p_list)
{
    cout << CNT_LIST_HEADER << endl;
    print_each_team_score_board(make_team_list(p_list, false));
    cout << TRR_LIST_HEADER << endl;
    print_each_team_score_board(make_team_list(p_list, true));
}

Status get_command_line(Status status, vector<string> splited_line)
{

    if (splited_line[0] == "add-user" && !status.start)
        status.p_list.push_back(add_user(splited_line[1], splited_line[2]));
    else if (splited_line[0] == "get-money")
        cout << find_user(splited_line[1], status.p_list).get_money() << endl;
    else if (splited_line[0] == "get-health")
        cout << find_user(splited_line[1], status.p_list).get_health() << endl;
    else if (splited_line[0] == "go-afk")
        status.p_list[find_user_idx(splited_line[1], status.p_list)].go_afk();
    else if (splited_line[0] == "go-atk")
        status.p_list[find_user_idx(splited_line[1], status.p_list)].go_atk();
    else if (splited_line[0] == "start")
    {
        status.start = true;
        cout << AFTER_START_MSG << endl;
    }
    else if (splited_line[0] == "buy")
    {
        if (find_user_idx(splited_line[1], status.p_list) == DOES_NOT_EXIST)
            cout << AFK_MSG << endl;
        else
            status.p_list[find_user_idx(splited_line[1], status.p_list)] = buy(splited_line[2], find_user(splited_line[1], status.p_list), status.start);
    }
    else if (splited_line[0] == "shoot")
        status.p_list = shoot(splited_line, status.p_list, status.start);
    else if (splited_line[0] == "score-board")
        print_score_board(status.p_list);
    return status;
}

bool terrorist_won(Player_list p_list)
{
    bool terrorist_won = true;
    for (int i = 0; i < p_list.size(); i++)
    {
        if (!p_list[i].get_is_terrorist() && p_list[i].get_health() && !p_list[i].get_afk())
            terrorist_won = false;
    }
    return terrorist_won;
}

Player_list reward_players(Player_list p_list, Reward rewards)
{
    for (int i = 0; i < p_list.size(); i++)
    {
        if (p_list[i].get_is_terrorist())
            p_list[i].money_inc(rewards.terrorist);
        else
            p_list[i].money_inc(rewards.counter_terrorist);
    }
    return p_list;
}

Player_list set_health(Player_list p_list)
{
    for (int i = 0; i < p_list.size(); i++)
        p_list[i].set_health();
    return p_list;
}

Status get_round_commands(Status status, int round_lines_num)
{
    string line;
    for (int i = 0; i < round_lines_num; i++)
    {
        getline(cin, line);
        vector<string> splited_string = split_line(line);
        status = get_command_line(status, splited_string);
    }
    return status;
}

Reward determine_reward(bool terr_won)
{
    Reward rewards;
    rewards.terrorist = (terr_won) ? WINNER_REWARD : LOSER_REWARD;
    rewards.counter_terrorist = (terr_won) ? LOSER_REWARD : WINNER_REWARD;
    return rewards;
}

Player_list determine_winner(Player_list p_list)
{
    bool terr_won = terrorist_won(p_list);
    cout << ((terr_won) ? TRR_WON_MSG : CNT_WON_MSG) << endl;
    p_list = reward_players(p_list, determine_reward(terr_won));
    return p_list;
}

Status play_a_round(Status status, int round_lines_num)
{
    status.p_list = set_health(status.p_list);
    status.start = false;
    status = get_round_commands(status, round_lines_num);
    status.p_list = determine_winner(status.p_list);
    return status;
}

Status switch_input(Status status, vector<string> splited_string)
{
    if (splited_string[0] == "add-user")
        status.p_list.push_back(add_user(splited_string[1], splited_string[2]));
    else if (splited_string[0] == "score-board")
        print_score_board(status.p_list);
    else if (splited_string[0] == "round")
        status = play_a_round(status, stoi(splited_string[1]));
    return status;
}

void play()
{
    string line;
    Status status;

    getline(cin, line);
    while (getline(cin, line))
    {
        vector<string> splited_string = split_line(line);
        status = switch_input(status, splited_string);
    }
}

int main()
{
    play();
    return 0;
}
