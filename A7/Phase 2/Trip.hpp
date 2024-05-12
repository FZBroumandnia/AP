#ifndef _TRIP_HPP
#define _TRIP_HPP
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
using namespace std;

#include "Consts.hpp"
#include "Location.hpp"
#include "Person.hpp"

class Trip
{
public:
    Trip(int _trip_id, Location _origin, Location _destination, Person *_passenger, double cost);

    bool same_passenger(Person *_passenger);
    bool same_status(int status);
    
    vector<string> trip_info();
    void change_status(int new_status);
    void set_driver(Person *_driver);
    bool is_more_expensive(Trip t2);
    bool is_not_waiting();

private:
    Location origin;
    Location destination;
    string passenger_name;
    int trip_id;
    int trip_status;
    double trip_cost;
    Person *passenger;
    Person *driver;
    string trip_status_string();
};
#endif