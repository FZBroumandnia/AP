#ifndef _IOHANDLER_HPP
#define _IOHANDLER_HPP
#include <iostream>
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
    void output(std::string msg);
    std::vector<std::string> get_command(string line);

private:
};
#endif