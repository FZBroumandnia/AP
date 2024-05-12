#include <iostream>
#include <string>
using namespace std;

const auto INITIAL_STRING = "0";
const auto ZERO_CHAR = '0';
const auto ONE_CHAR = '1';
const auto REPLACEMENT_OF_0 = "01";
const auto REPLACEMENT_OF_1 = "10";

void print_char(string input_string, int kth_char)
{
    cout << input_string[kth_char - 1] << endl;
}

string calculate_string(string input_string, int nth_stage)
{
    if (nth_stage == 1)
        return input_string;
    else
    {
        string output_string;
        for (int i = 0; i < input_string.size(); i++)
        {
            if (input_string[i] == ZERO_CHAR)
                output_string += REPLACEMENT_OF_0;
            else if (input_string[i] == ONE_CHAR)
                output_string += REPLACEMENT_OF_1;
        }
        return calculate_string(output_string, nth_stage - 1);
    }
}

int main()
{
    int nth_stage;
    long long kth_char;
    cin >> nth_stage >> kth_char;
    print_char(calculate_string(INITIAL_STRING, nth_stage), kth_char);
}