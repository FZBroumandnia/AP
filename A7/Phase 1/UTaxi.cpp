#include "UTaxi.hpp"
UTaxi::UTaxi(char *file)
{
    File_handler file_handler;
    locs = file_handler.read_locations(file);
}

void UTaxi::get_command()
{
    string line;
    while (getline(std::cin, line))
    {
        command = ioh.get_command(line);
        command_t = ioh.tokenize_command(line);
        try
        {
            if (!command_t.id_in_range(trips.size()))
                throw Exception_handler(Not_found);
            if (command[0] == "POST")
                handle_post();
            if (command[0] == "GET")
                handle_get();
            if (command[0] == "DELETE")
                handle_delete();
        }
        catch (Exception_handler ex)
        {
            ioh.output(ex.error_message());
        }
    }
}
void UTaxi::handle_post()
{
    if (command[1] == "trips")
    {
        post_trips();
        return;
    }
    if (command[1] == "signup")
        signup();
    if (command[1] == "accept")
        post_accept();
    if (command[1] == "finish")
        post_finish();
    ioh.output(OK);
};
void UTaxi::handle_get()
{
    Person *user_p = find_user(command_t.get_username());
    user_p->get_trip();
    if (command[1] == "trips" && command.size() == 5)
        print_all_trips();
    if (command[1] == "trips" && command.size() == 7)
        trips[stoi(command_t.get_id()) - 1]->print_trip();
};
void UTaxi::handle_delete()
{
    if (command[1] == "trips")
        delete_trips();
    ioh.output("OK");
};

bool UTaxi::correct_passenger(Person *per, int trip_id)
{
    if (trips[trip_id]->same_passenger(per))
        return true;
    return false;
}
bool UTaxi::has_ongoing_trip(int trip_id)
{
    if (trips[trip_id]->same_status(Finished) || trips[trip_id]->same_status(traveling))
        return true;
    return false;
}
bool UTaxi::canceled_before(int trip_id)
{
    if (trips[trip_id]->same_status(Canceled))
        return true;
    return false;
}

void UTaxi::delete_trips()
{
    Person *user_p = find_user(command_t.get_username());
    if (!user_p)
        throw Exception_handler(Not_found);
    user_p->delete_trip();
    if (has_ongoing_trip(stoi(command_t.get_id()) - 1))
        throw Exception_handler(Bad_Req);
    if (canceled_before(stoi(command_t.get_id()) - 1))
        throw Exception_handler(Not_found);
    if (!correct_passenger(user_p, stoi(command_t.get_id()) - 1))
        throw Exception_handler(Permission_denied);
    trips[stoi(command_t.get_id()) - 1]->change_status(Canceled);
}
void UTaxi::print_all_trips()
{
    bool empty = true;
    if (!trips.size())
        throw Exception_handler(Empty);

    for (Trip *t : trips)
    {
        if (!t->same_status(Canceled))
        {
            t->print_trip();
            empty = false;
        }
    }
    if (empty)
        throw Exception_handler(Empty);
}

Person *UTaxi::find_user(string username)
{
    for (Person *p : users)
    {
        if (p->same_name(username))
            return p;
    }
    return NULL;
}

Location UTaxi::find_loc(std::string name)
{
    for (Location loc : locs)
    {
        if (name == loc.name)
            return loc;
    }
    throw Exception_handler(Not_found);
}

bool UTaxi::check_trip_status(Person *per, int trip_type)
{
    for (int i = 0; i < trips.size(); i++)
    {
        if (trips[i]->same_passenger(per) && trips[i]->same_status(trip_type))
            return false;
    }
    return true;
}

void UTaxi::post_trips()
{
    Person *user_p = find_user(command_t.get_username());
    if (!user_p)
        throw Exception_handler(Not_found);
    if (!check_trip_status(user_p, traveling))
        throw Exception_handler(Bad_Req);
    user_p->post_trip();
    if (command_t.is_empty())
        throw Exception_handler(Bad_Req);
    Location origin = find_loc(command_t.get_origin());
    Location destination = find_loc(command_t.get_destination());

    Trip *new_trip = new Trip(user_p->get_name(), trips.size() + 1, origin, destination, user_p);
    trips.push_back(new_trip);
    ioh.output(to_string(trips.size()));
}

void UTaxi::post_finish()
{
    Person *user_p = find_user(command_t.get_username());
    if (!user_p)
        throw Exception_handler(Not_found);
    user_p->post_finish();
    trips[stoi(command_t.get_id()) - 1]->change_status(Finished);
}

void UTaxi::post_accept()
{
    Person *user_p = find_user(command_t.get_username());
    if (!user_p)
        throw Exception_handler(Not_found);
    if (!check_trip_status(user_p, traveling))
        throw Exception_handler(Bad_Req);

    user_p->post_accept();
    trips[stoi(command_t.get_id()) - 1]->change_status(traveling);
    trips[stoi(command_t.get_id()) - 1]->set_driver(user_p);
}
void UTaxi::signup()
{
    if (find_user(command_t.get_username()))
        throw Exception_handler(Bad_Req);
    if (command_t.get_role() == "driver")
    {
        Driver *new_driver = new Driver(command_t.get_username());
        users.push_back(new_driver);
    }
    else if (command_t.get_role() == "passenger")
    {
        Passenger *new_pass = new Passenger(command_t.get_username());
        users.push_back(new_pass);
    }
    else
        throw Exception_handler(Bad_Req);
}
UTaxi::~UTaxi()
{
    while (!trips.empty())
    {
        delete trips.back();
        trips.pop_back();
    }
    while (!users.empty())
    {
        delete users.back();
        users.pop_back();
    }
}