#ifndef _CONSTS_HPP
#define _CONSTS_HPP
#include <iostream>
#include <string>

const char COMMA = ',';
const char SPACE = ' ';
const std::string PERMISSION_ERR = "Permission Denied";
const std::string BAD_REQ = "Bad Request";
const std::string NF = "Not Found";
const std::string EMPTY = "EMPTY";
const std::string OK = "OK";

enum trip_status
{
    waiting,
    traveling,
    Finished,
    Canceled,
};

enum exception_types
{
    Not_found,
    Bad_Req,
    Empty,
    Permission_denied,
};
struct Location
{
    std::string name;
    double latitude;
    double longitude;
};
#endif