#include "Trip.hpp"
Trip::Trip(string _passenger_name, int _trip_id, Location _origin, Location _destination, Person *_passenger)
{
    passenger_name = _passenger_name;
    trip_id = _trip_id;
    origin = _origin;
    destination = _destination;
    trip_status = waiting;
    passenger = _passenger;
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

bool Trip::same_status(int status)
{
    if (status == trip_status)
        return true;
    return false;
}
string Trip::print_status()
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
void Trip::print_trip()
{
    std::cout << trip_id << SPACE
              << passenger_name << SPACE
              << origin.name << SPACE
              << destination.name << SPACE
              << print_status() << std::endl;
}
void Trip::change_status(int new_status)
{
    trip_status = new_status;
}
void Trip::set_driver(Person *_driver)
{
    driver = _driver;
}