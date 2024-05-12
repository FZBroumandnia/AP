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
    else if (command[1] == "signup")
        signup();
    else if (command[1] == "accept")
        post_accept();
    else if (command[1] == "finish")
        post_finish();
    else
    {
        throw Exception_handler(Not_found);
    }
    ioh.output(OK);
};
void UTaxi::handle_get()
{
    Person *user_p = find_user(command_t.get_username());

    if (command[1] == "cost")
    {
        handle_cost();
        return;
    }
    user_p->get_trip();
    if (command[1] == "trips" && !command_t.is_specified())
        print_all_trips();
    else if (command[1] == "trips" && command_t.is_specified())
        ioh.print_trip(trips[stoi(command_t.get_id()) - 1]->trip_info());
    else
    {
        throw Exception_handler(Not_found);
    }
};

double UTaxi::calculate_price(Location loc1, Location loc2, bool in_hurry)
{
    double cost = loc1.calculate_distance(loc2) * (loc1.get_traffic() + loc2.get_traffic()) * PRICE_CONST;
    if (!in_hurry)
        return cost;
    else
        return IN_HURRY_CONST * cost;
}

double UTaxi::handle_cost()
{
    Person *user_p = find_user(command_t.get_username());
    if (!user_p)
        throw Exception_handler(Not_found);
    if (command_t.is_empty())
        throw Exception_handler(Bad_Req);
    user_p->get_cost();
    Location origin = find_loc(command_t.get_origin());
    Location destination = find_loc(command_t.get_destination());
    bool in_hurry = command_t.in_hurry_to_bool();
    ioh.print_cost(calculate_price(origin, destination, in_hurry));
    return calculate_price(origin, destination, in_hurry);
}

void UTaxi::handle_delete()
{
    if (command[1] == "trips")
        delete_trips();
    else
    {
        throw Exception_handler(Not_found);
    }
    ioh.output("OK");
};

void UTaxi::delete_trips()
{
    Person *user_p = find_user(command_t.get_username());
    int trip_idx = stoi(command_t.get_id()) - 1;
    if (!user_p)
        throw Exception_handler(Not_found);
    user_p->delete_trip();
    if (trips[trip_idx]->is_not_waiting())
        throw Exception_handler(Bad_Req);
    if (trips[trip_idx]->same_status(Canceled))
        throw Exception_handler(Not_found);
    if (!trips[trip_idx]->same_passenger(user_p))
        throw Exception_handler(Permission_denied);
    trips[trip_idx]->change_status(Canceled);
}

int UTaxi::find_best_idx(vector<bool> sorted)
{
    int best_idx = 0;
    for (int i = 0; i < trips.size(); i++)
    {
        if (sorted[i])
            continue;
        while (sorted[best_idx])
            best_idx++;
        if (trips[best_idx]->is_more_expensive(*trips[i]))
            best_idx = i;
    }
    return best_idx;
}

bool UTaxi::all_sorted(vector<bool> sorted)
{
    for (bool p : sorted)
    {
        if (!p)
            return false;
    }
    return true;
}

bool UTaxi::handle_sorted_trips()
{
    bool empty = true;
    vector<bool> sorted(trips.size(), false);
    while (!all_sorted(sorted))
    {
        int best_idx = find_best_idx(sorted);
        if (!trips[best_idx]->same_status(Canceled))
        {
            ioh.print_trip(trips[best_idx]->trip_info());
            empty = false;
        }
        sorted[best_idx] = true;
    }
    return empty;
}

bool UTaxi::handle_unsorted_trips()
{
    bool empty = true;
    for (Trip *t : trips)
    {
        if (!t->same_status(Canceled))
        {
            ioh.print_trip(t->trip_info());
            empty = false;
        }
    }
    return empty;
}

void UTaxi::print_all_trips()
{
    bool empty = true;
    if (!trips.size())
        throw Exception_handler(Empty);

    if (command_t.sort_to_bool())
        empty = handle_sorted_trips();
    else
        empty = handle_unsorted_trips();
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
        if (loc.same_name(name))
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
    bool in_hurry = command_t.in_hurry_to_bool();
    Trip *new_trip = new Trip(trips.size() + 1, origin, destination, user_p, calculate_price(origin, destination, in_hurry));
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
    int trip_idx = stoi(command_t.get_id()) - 1;
    if (!user_p)
        throw Exception_handler(Not_found);
    if (!check_trip_status(user_p, traveling))
        throw Exception_handler(Bad_Req);
    if (trips[trip_idx]->is_not_waiting())
        throw Exception_handler(Bad_Req);

    user_p->post_accept();
    trips[trip_idx]->change_status(traveling);
    trips[trip_idx]->set_driver(user_p);
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