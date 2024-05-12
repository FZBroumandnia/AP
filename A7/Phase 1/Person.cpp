#include "Person.hpp"
Person::Person(string _username)
{
    username = _username;
}
bool Person::same_name(string _username)
{
    if (_username == username)
        return true;
    return false;
}