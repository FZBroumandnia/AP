#ifndef _UTaxi_HPP
#define _UTaxi_HPP
#include <string>
#include <vector>
#include <cmath>

#include "Consts.hpp"
#include "File_handler.hpp"
#include "Iohandler.hpp"
#include "Command_token.hpp"
#include "Person.hpp"
#include "Passenger_driver.hpp"
#include "Trip.hpp"
#include "Exception_handler.hpp"
#include "Location.hpp"

class UTaxi
{
public:
    UTaxi(char *file);
    void get_command();
    void handle_post();
    void handle_get();
    void handle_delete();

    void post_trips();
    void post_finish();
    void post_accept();
    void signup();
    void delete_trips();
    double handle_cost();
    void print_all_trips();

    bool handle_sorted_trips();
    bool handle_unsorted_trips();

    double calculate_price(Location loc1, Location loc2, bool in_hurry);
    ~UTaxi();

private:
    Iohandler ioh;
    Command_Token command_t;
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