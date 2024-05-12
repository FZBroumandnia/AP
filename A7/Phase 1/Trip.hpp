#ifndef _TRIP_HPP
#define _TRIP_HPP
#include <string>
#include <vector>
using namespace std;

#include "Consts.hpp"
#include "Person.hpp"

class Trip
{
public:
    Trip(string _passenger_name, int _trip_id, Location _origin, Location _destination, Person *_passenger);

    bool same_passenger(Person *_passenger);
    bool same_status(int status);

    string print_status();
    void print_trip();
    void change_status(int new_status);
    void set_driver(Person *_driver);

private:
    Location origin;
    Location destination;
    string passenger_name;
    int trip_id;
    int trip_status;
    Person *passenger;
    Person *driver;
};
#endif