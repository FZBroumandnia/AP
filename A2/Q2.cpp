#include <iostream>
#include <string>
#include <vector>
using namespace std;

const auto TRUE_MESSAGE = "Interleaving";
const auto FALSE_MESSAGE = "Not Interleaving";

struct Strings
{
    string first;
    string second;
    string compound;
};

struct Indexes
{
    int compound_str;
    int first_str;
};
Indexes INITIAL_INDEX = {0, 0};

bool check_remained_compund_idxs(vector<int> compund_idxs_belong_to_first_str, Strings str)
{
    for (int i = 0; i < compund_idxs_belong_to_first_str.size(); i++)
        str.compound.erase(str.compound.begin() + compund_idxs_belong_to_first_str[i] - i);
    if (str.compound == str.second)
        return true;
    else
        return false;
}

bool check_compound_str(vector<int> compund_idxs_belong_to_first_str, Strings str, Indexes idx)
{
    if (idx.first_str >= str.first.size())
    {
        if (check_remained_compund_idxs(compund_idxs_belong_to_first_str, str))
            return true;
        else
            return false;
    }

    if (idx.compound_str >= str.compound.size())
        return false;

    for (idx.compound_str; idx.compound_str < str.compound.size(); idx.compound_str = idx.compound_str + 1)
    {
        if (str.compound[idx.compound_str] == str.first[idx.first_str])
        {
            compund_idxs_belong_to_first_str.push_back(idx.compound_str);
            Indexes new_idx = {idx.compound_str + 1, idx.first_str + 1};
            if (check_compound_str(compund_idxs_belong_to_first_str, str, new_idx))
                return true;
            else
                compund_idxs_belong_to_first_str.pop_back();
        }
    }
    return false;
}

void print_result(int input)
{
    if (input)
        cout << TRUE_MESSAGE << endl;
    else
        cout << FALSE_MESSAGE << endl;
}

int main()
{
    Strings str;
    cin >> str.first >> str.second >> str.compound;
    vector<int> compund_idxs_belong_to_first_str;
    print_result(check_compound_str(compund_idxs_belong_to_first_str, str, INITIAL_INDEX));
}