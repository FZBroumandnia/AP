#include "Trip.hpp"
Trip::Trip(int _trip_id, Location _origin, Location _destination, Person *_passenger, double cost) : origin(_origin), destination(_destination)
{
    passenger_name = _passenger->get_name();
    trip_id = _trip_id;
    origin = _origin;
    destination = _destination;
    trip_status = waiting;
    passenger = _passenger;
    trip_cost = cost;
    driver = NULL;
}

bool Trip::same_passenger(Person *_passenger)
{
    if (_passenger->get_name() == passenger->get_name())
    {
        return true;
    }
    if (driver && _passenger->get_name() == driver->get_name())
    {
        return true;
    }
    return false;
}

bool Trip::same_driver(string _username)
{
    if (driver && _username == driver->get_name())
    {
        return true;
    }
    return false;
}

bool Trip::same_status(int status)
{
    if (status == trip_status)
    {
        return true;
    }
    return false;
}
string Trip::trip_status_string()
{
    switch (trip_status)
    {
    case waiting:
        return "waiting";
        break;
    case traveling:
        return "traveling";
    case Finished:
        return "finished";

    default:
        return "finished";
        break;
    }
}
vector<string> Trip::trip_info()
{
    std::ostringstream trip_stream;
    trip_stream << std::fixed;
    trip_stream << std::setprecision(2);
    trip_stream << trip_cost;
    std::string trip_cost_string = trip_stream.str();
    vector<string> trip_info{to_string(trip_id), passenger_name, origin.get_name(), destination.get_name(), trip_cost_string, trip_status_string()};
    return trip_info;
}
void Trip::change_status(int new_status)
{
    trip_status = new_status;
}
void Trip::set_driver(Person *_driver)
{
    driver = _driver;
}

bool Trip::is_more_expensive(Trip t2)
{
    if (trip_cost < t2.trip_cost)
        return true;
    return false;
}

bool Trip::is_not_waiting()
{
    if (trip_status == traveling || trip_status == Finished)
        return true;
    return false;
}