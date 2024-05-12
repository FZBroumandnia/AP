#ifndef _EXCEPTION_HANDLER_HPP
#define _EXCEPTION_HANDLER_HPP
#include<string>
using namespace std;

#include "Consts.hpp"

class Exception_handler
{
public:
    Exception_handler(int _type);
    string error_message();

private:
    int exception_type;
};
#endif