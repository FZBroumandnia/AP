#ifndef _UTaxi_HPP
#define _UTaxi_HPP
#include <string>
#include <vector>
#include <cmath>

#include "Consts.hpp"
#include "File_handler.hpp"
#include "Person.hpp"
#include "Passenger_driver.hpp"
#include "Trip.hpp"
#include "Exception_handler.hpp"
#include "Location.hpp"

class UTaxi
{
public:
    UTaxi(char *file);
    void handle_get(string username);

    void post_trips(string _username, string _origin, string _destination, bool hurry);
    void post_finish(string _username, string _id);
    void post_accept(string _username, string _id);
    void signup(string username, string type);
    void delete_trips(string _username, string _id);
    double handle_cost(string _username, string _origin, string _destination, bool hurry);

    vector<Trip*> handle_sorted_trips();
    bool handle_unsorted_trips();

    vector<Trip*> get_all_trips(){return trips;}
    int get_trips_size(){return trips.size();}
    double calculate_price(Location loc1, Location loc2, bool in_hurry);
    ~UTaxi();

private:
    vector<Location> locs;
    vector<string> command;
    vector<Person *> users;
    vector<Trip *> trips;

    Person *find_user(string username);
    Location find_loc(std::string name);

    int find_best_idx(vector<bool> printed);
    bool all_sorted(vector<bool> printed);
    bool check_trip_status(Person *per, int trip_type);
};
#endif