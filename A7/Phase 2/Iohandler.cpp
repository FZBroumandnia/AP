#include "Iohandler.hpp"

Command_Token Iohandler::tokenize_command(string line)
{
    Command_Token command_t;
    command_t.tokenize(get_command(line));
    return command_t;
}
void Iohandler::output(std::string msg)
{
    std::cout << msg << std::endl;
}

void Iohandler::print_cost(double cost)
{
    std::cout << std::setprecision(2) << std::fixed << cost << std::endl;
}

std::vector<std::string> Iohandler::split_line(std::string line, char delimiter)
{
    std::stringstream new_line(line);
    std::string splited_str;
    std::vector<std::string> splited_vector;
    while (getline(new_line, splited_str, delimiter))
        splited_vector.push_back(splited_str);
    return splited_vector;
}

std::vector<std::string> Iohandler::get_command(string line)
{
    return split_line(line, SPACE);
}

void Iohandler::print_trip(vector<string> trip_info)
{
    std::cout << trip_info[0] << SPACE
              << trip_info[1] << SPACE
              << trip_info[2] << SPACE
              << trip_info[3] << SPACE
              << trip_info[4] << SPACE
              << trip_info[5] << std::endl;
}