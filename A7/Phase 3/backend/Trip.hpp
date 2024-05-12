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
    string get_id()
    {
        return to_string(trip_id);
    }
    string get_passenger() { return passenger_name; }
    string get_origin() { return origin.get_name(); }
    string get_destination() { return destination.get_name(); }
    string get_trip_cost()
    {
        std::ostringstream trip_stream;
        trip_stream << std::fixed;
        trip_stream << std::setprecision(2);
        trip_stream << trip_cost;
        std::string trip_cost_string = trip_stream.str();
        return trip_cost_string;
    }
    string trip_status_string();

    bool same_passenger(Person *_passenger);
    bool same_driver(string _username);
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
    
};
#endif