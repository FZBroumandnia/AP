#include "Location.hpp"

Location::Location(std::string _name, double _latitude, double _longitude, int _traffic)
{
    name = _name;
    latitude = _latitude;
    longitude = _longitude;
    traffic = _traffic;
}

double Location::calculate_distance(Location loc2)
{
    return DISTANCE_CONST * sqrt(pow((loc2.latitude - latitude), 2) + pow((loc2.longitude - longitude), 2));
}

bool Location::same_name(std::string _name)
{
    if (name == _name)
        return true;
    return false;
}
