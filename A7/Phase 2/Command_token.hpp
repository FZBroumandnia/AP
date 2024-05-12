#ifndef _COMMAND_TOKEN_HPP
#define _COMMAND_TOKEN_HPP

#include <vector>
#include <string>
using namespace std;

class Command_Token
{
public:
    void tokenize(vector<string> _command_line);
    bool is_empty();
    bool id_in_range(int size);
    bool in_hurry_to_bool();
    bool sort_to_bool();
    bool is_specified();

    string get_username() { return username; }
    string get_role() { return role; }
    string get_id() { return trip_id; }
    string get_destination() { return destination; }
    string get_origin() { return origin; }

private:
    vector<string> command_line;
    string username;
    string role;
    string trip_id;
    string origin;
    string destination;
    string in_hurry;
    string sort;
};
#endif