#ifndef _IOHANDLER_HPP
#define _IOHANDLER_HPP
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
#include "Command_token.hpp"
#include "Consts.hpp"

class Iohandler
{
public:
    Command_Token tokenize_command(string line);
    std::vector<std::string> split_line(std::string line, char delimiter);
    std::vector<std::string> get_command(string line);
    void output(std::string msg);
    void print_cost(double cost);
    void print_trip(vector<string> trip_info);

private:
};
#endif