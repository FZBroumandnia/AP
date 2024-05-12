#ifndef _PERSON_HPP
#define _PERSON_HPP
#include <string>
using namespace std;
class Person
{
public:
    Person(string _username);
    bool same_name(string _username);
    string get_name() { return username; }
    
    virtual void post_trip() = 0;
    virtual void get_trip() = 0;
    virtual void post_finish() = 0;
    virtual void post_accept() = 0;
    virtual void delete_trip() = 0;
    virtual void get_cost() = 0;

private:
    string username;
};
#endif