#include "File_handler.hpp"
std::vector<std::string> File_handler::token_file(std::string line, char delimiter)
{
    std::stringstream new_line(line);
    std::string splited_str;
    std::vector<std::string> splited_vector;
    while (getline(new_line, splited_str, delimiter))
        splited_vector.push_back(splited_str);
    return splited_vector;
}

Location File_handler::read_location(std::string line)
{
    std::vector<std::string> splitted = token_file(line, COMMA);
    return Location(splitted[0], stod(splitted[1]), stod(splitted[2]), stoi(splitted[3]));
}

std::vector<Location> File_handler::handle_line_location(ifstream &loc_file)
{
    std::vector<Location> locations;
    std::string line;
    getline(loc_file, line);
    while (getline(loc_file, line))
        locations.push_back(read_location(line));
    return locations;
}

std::vector<Location> File_handler::read_locations(const char *file)
{

    std::ifstream loc_file;
    loc_file.open(file);
    return handle_line_location(loc_file);
}