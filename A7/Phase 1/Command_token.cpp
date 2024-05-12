#include "Command_token.hpp"

void Command_Token::tokenize(vector<string> _command_line)
{
    command_line = _command_line;
    for (int i = 0; i < command_line.size(); i++)
    {
        if (command_line[i] == "username")
            username = command_line[i + 1];
        if (command_line[i] == "role")
            role = command_line[i + 1];
        if (command_line[i] == "id")
            trip_id = command_line[i + 1];
        if (command_line[i] == "origin")
            origin = command_line[i + 1];
        if (command_line[i] == "destination")
            destination = command_line[i + 1];
    }
}
bool Command_Token::is_empty()
{
    if (username.empty() || origin.empty() || destination.empty())
        return true;
    return false;
}
bool Command_Token::id_in_range(int size)
{
    if (trip_id.empty())
        return true;
    if (stoi(trip_id) > 0 && stoi(trip_id) <= size)
        return true;
    return false;
}