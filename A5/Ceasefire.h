#ifndef CEASEFIRE_H
#define CEASEFIRE_H
#include <iostream>
#include <vector>

using namespace std;

class Ceasefire_col
{
public:
    Ceasefire_col(int _cols, int _mode);
    void set(int _cols, int _mode);
    vector<bool> get_ceasefire_col_bool();
    void make_ceasefire_col();

private:
    int cols;
    int mode;
    vector<bool> ceasefire_col_bool;
    vector<int> ceasefire_col_idx;
    bool in_range(int upper_lim, int num);
    void set_initial_ceasefire_col();
    vector<int> make_new_ceasefire_col_idx();
    vector<vector<int>> make_approximate_col();
    vector<bool> choose_from_non_approximate(bool added, vector<bool> new_ceasefire_col_bool);
};

#endif