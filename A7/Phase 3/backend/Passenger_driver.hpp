#ifndef _PASSENGER_DRIVER_HPP
#define _PASSENGER_DRIVER_HPP

#include "Person.hpp"
#include "Exception_handler.hpp"

class Driver : public Person
{
public:
    Driver(string _username) : Person(_username){};
    void post_finish(){};
    void post_accept(){};
    void get_trip(){};
    void delete_trip()
    {
        throw Exception_handler(Permission_denied);
    };
    void post_trip()
    {
        throw Exception_handler(Permission_denied);
    }
    void get_cost()
    {
        throw Exception_handler(Permission_denied);
    };

private:
};
class Passenger : public Person
{
public:
    Passenger(string _username) : Person(_username){};
    void post_trip(){};
    void delete_trip(){};
    void get_trip()
    {
        throw Exception_handler(Permission_denied);
    }
    void post_finish()
    {
        throw Exception_handler(Permission_denied);
    }
    void post_accept()
    {
        throw Exception_handler(Permission_denied);
    }
    void get_cost(){};

private:
};
#endif