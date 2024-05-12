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

const double DISTANCE_CONST = 110.5;
const double IN_HURRY_CONST = 1.2;
const int PRICE_CONST = 10000;

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

#endif