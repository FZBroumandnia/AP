#include "Ceasefire.h"

Ceasefire_col::Ceasefire_col(int _cols, int _mode)
{
    cols = _cols;
    mode = _mode;
}

void Ceasefire_col::set(int _cols, int _mode)
{
    cols = _cols;
    mode = _mode;
    set_initial_ceasefire_col();
}

bool Ceasefire_col::in_range(int upper_lim, int num)
{
    if (num >= 0 && num < upper_lim)
        return true;
    else
        return false;
}

void Ceasefire_col::set_initial_ceasefire_col()
{
    vector<bool> chosen(cols, false);
    ceasefire_col_idx.clear();
    for (int i = 0; i < mode; i++)
    {
        int new_num = rand() % cols;
        while (chosen[new_num])
            new_num = rand() % cols;
        ceasefire_col_idx.push_back(new_num);
        chosen[new_num] = true;
    }
    ceasefire_col_bool = chosen;
}
vector<bool> Ceasefire_col::get_ceasefire_col_bool()
{
    return ceasefire_col_bool;
};

vector<vector<int>> Ceasefire_col::make_approximate_col()
{
    vector<vector<int>> approximate(ceasefire_col_idx.size());
    for (int i = 0; i < ceasefire_col_idx.size(); i++)
    {
        if (in_range(cols, ceasefire_col_idx[i] - 1))
            approximate[i].push_back(ceasefire_col_idx[i] - 1);
        if (in_range(cols, ceasefire_col_idx[i] + 1))
            approximate[i].push_back(ceasefire_col_idx[i] + 1);
    }
    return approximate;
}
vector<int> Ceasefire_col::make_new_ceasefire_col_idx()
{
    vector<int> new_ceasefire_col_idx;
    for (int i = 0; i < ceasefire_col_bool.size(); i++)
    {
        if (ceasefire_col_bool[i])
            new_ceasefire_col_idx.push_back(i);
    }
    return new_ceasefire_col_idx;
}

vector<bool> Ceasefire_col::choose_from_non_approximate(bool added, vector<bool> new_ceasefire_col_bool)
{
    if (!added)
    {
        int new_num = rand() % cols;
        while (new_ceasefire_col_bool[new_num])
            new_num = rand() % cols;
        new_ceasefire_col_bool[new_num] = true;
    }
    return new_ceasefire_col_bool;
}

void Ceasefire_col::make_ceasefire_col()
{
    vector<vector<int>> approximate = make_approximate_col();
    vector<bool> new_ceasefire_col_bool(cols, false);
    for (int i = 0; i < ceasefire_col_idx.size(); i++)
    {
        bool added = false;

        if (approximate[i].size() == 1)
        {
            if (!new_ceasefire_col_bool[approximate[i][0]])
            {
                new_ceasefire_col_bool[approximate[i][0]] = true;
                added = true;
            }
        }
        else if (approximate[i].size() == 2)
        {
            int rand_idx = rand() % 2;
            if (!rand_idx && !new_ceasefire_col_bool[approximate[i][0]])
            {
                new_ceasefire_col_bool[approximate[i][0]] = true;
                added = true;
            }

            else if (rand_idx && !new_ceasefire_col_bool[approximate[i][1]])
            {
                new_ceasefire_col_bool[approximate[i][1]] = true;
                added = true;
            }
        }
        new_ceasefire_col_bool = choose_from_non_approximate(added, new_ceasefire_col_bool);
    }
    ceasefire_col_bool.clear();
    ceasefire_col_bool = new_ceasefire_col_bool;
    ceasefire_col_idx.clear();
    ceasefire_col_idx = make_new_ceasefire_col_idx();
}