#include <iostream>
#include <vector>
using namespace std;

const auto TRUE_MESSAGE = "True";
const auto FALSE_MESSAGE = "False";

vector<int> input_weights(int number_of_weights)
{
    vector<int> weights;
    int new_weight;
    for (int i = 0; i < number_of_weights; i++)
    {
        cin >> new_weight;
        weights.push_back(new_weight);
    }
    return weights;
}

bool measure(vector<int> &weights, int mass, int weights_idx)
{
    if (!mass)
        return true;
    if (weights_idx == weights.size())
        return false;
    for (weights_idx; weights_idx < weights.size(); weights_idx++)
    {
        int minus = mass - weights[weights_idx];
        int sum = mass + weights[weights_idx];
        if (measure(weights, minus, weights_idx + 1))
            return true;
        if (measure(weights, sum, weights_idx + 1))
            return true;
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
    int number_of_weights, mass;
    cin >> number_of_weights >> mass;
    vector<int> weights = input_weights(number_of_weights);
    print_result(measure(weights, mass, 0));
}