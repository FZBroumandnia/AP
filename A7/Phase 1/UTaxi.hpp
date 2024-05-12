#ifndef _UTaxi_HPP
#define _UTaxi_HPP
#include <string>
#include <vector>

#include "Consts.hpp"
#include "File_handler.hpp"
#include "Iohandler.hpp"
#include "Command_token.hpp"
#include "Person.hpp"
#include "Passenger_driver.hpp"
#include "Trip.hpp"
#include "Exception_handler.hpp"

class UTaxi
{
public:
    UTaxi(char *file);
    void get_command();
    void handle_post();
    void handle_get();
    void handle_delete();

    bool correct_passenger(Person *per, int trip_id);
    bool has_ongoing_trip(int trip_id);
    bool canceled_before(int trip_id);
    bool check_trip_status(Person *per, int trip_type);

    Person *find_user(string username);
    Location find_loc(std::string name);

    void post_trips();
    void post_finish();
    void post_accept();
    void signup();
    void delete_trips();
    void print_all_trips();
    ~UTaxi();

private:
    Iohandler ioh;
    Command_Token command_t;
    vector<Location> locs;
    vector<string> command;
    vector<Person *> users;
    vector<Trip *> trips;
};
#endif