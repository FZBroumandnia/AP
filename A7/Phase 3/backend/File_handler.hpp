#ifndef _FILE_HANDLER_HPP
#define _FILE_HANDLER_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Consts.hpp"
#include "Location.hpp"
using namespace std;

class File_handler
{
public:
    std::vector<std::string> token_file(std::string line, char delimiter);
    Location read_location(std::string line);
    std::vector<Location> read_locations(const char *file);
    std::vector<Location> handle_line_location(std::ifstream &file);

private:
};

#endif