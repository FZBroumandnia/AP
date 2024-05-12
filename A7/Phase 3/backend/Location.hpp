#ifndef _LOCATION_HPP
#define _LOCATION_HPP
#include <string>
#include <cmath>

#include "Consts.hpp"

class Location
{
public:
    Location();
    Location(std::string _name, double _latitude, double _longitude, int _traffic);
    double calculate_distance(Location loc2);
    bool same_name(std::string _name);

    int get_traffic() { return traffic; }
    std::string get_name() { return name; }

private:
    std::string name;
    double latitude;
    double longitude;
    int traffic;
};
#endif