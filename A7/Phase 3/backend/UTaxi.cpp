#include "UTaxi.hpp"
UTaxi::UTaxi(char *file)
{
    File_handler file_handler;
    locs = file_handler.read_locations(file);
}

void UTaxi::handle_get(string _username)
{
    Person *user_p = find_user(_username);
    if (_username.empty())
        throw Exception_handler(Bad_Req);
    if (!user_p)
        throw Exception_handler(Not_found);

    user_p->get_trip();
};

double UTaxi::calculate_price(Location loc1, Location loc2, bool in_hurry)
{
    double cost = loc1.calculate_distance(loc2) * (loc1.get_traffic() + loc2.get_traffic()) * PRICE_CONST;
    if (!in_hurry)
        return cost;
    else
        return IN_HURRY_CONST * cost;
}

double UTaxi::handle_cost(string _username, string _origin, string _destination, bool hurry)
{
    Person *user_p = find_user(_username);
    if (!user_p)
        throw Exception_handler(Not_found);
    if (_username.empty() || _origin.empty() || _destination.empty())
        throw Exception_handler(Bad_Req);
    user_p->get_cost();
    Location origin = find_loc(_origin);
    Location destination = find_loc(_destination);
    bool in_hurry = hurry;
    return calculate_price(origin, destination, in_hurry);
}


void UTaxi::delete_trips(string _username, string _id)
{
    Person *user_p = find_user(_username);
    if (_username.empty() || _id.empty())
        throw Exception_handler(Bad_Req);    
    int trip_idx = stoi(_id) - 1;
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

vector<Trip *> UTaxi::handle_sorted_trips()
{
    bool empty = true;
    vector<bool> sorted(trips.size(), false);
    vector<Trip *> sorted_trips;
    while (!all_sorted(sorted))
    {
        int best_idx = find_best_idx(sorted);
        if (!trips[best_idx]->same_status(Canceled))
        {
            sorted_trips.push_back(trips[best_idx]);
            empty = false;
        }
        sorted[best_idx] = true;
    }
    return sorted_trips;
}

bool UTaxi::handle_unsorted_trips()
{
    bool empty = true;
    for (Trip *t : trips)
    {
        if (!t->same_status(Canceled))
            empty = false;
    }
    return empty;
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
        {
            return false;
        }
    }
    return true;
}

void UTaxi::post_trips(string _username, string _origin, string _destination, bool hurry)
{
    Person *user_p = find_user(_username);
    if (_username.empty() || _origin.empty() || _destination.empty())
        throw Exception_handler(Bad_Req);
    if (!user_p)
        throw Exception_handler(Not_found);
    if (!check_trip_status(user_p, traveling))
        throw Exception_handler(Bad_Req);
    user_p->post_trip();    
    Location origin = find_loc(_origin);
    Location destination = find_loc(_destination);
    bool in_hurry = hurry;
    Trip *new_trip = new Trip(trips.size() + 1, origin, destination, user_p, calculate_price(origin, destination, in_hurry));
    trips.push_back(new_trip);
}

void UTaxi::post_finish(string _username, string _id)
{
    Person *user_p = find_user(_username);
    if (!user_p)
        throw Exception_handler(Not_found);
    user_p->post_finish();
    trips[stoi(_id) - 1]->change_status(Finished);
}

void UTaxi::post_accept(string _username, string _id)
{
    Person *user_p = find_user(_username);
    int trip_idx = stoi(_id) - 1;
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

void UTaxi::signup(string username, string type)
{
    if (username.empty())
    {
        throw Exception_handler(Bad_Req);
    }
    if (find_user(username))
    {
        throw Exception_handler(Bad_Req);
    }

    if (type == "driver")
    {
        Driver *new_driver = new Driver(username);
        users.push_back(new_driver);
    }
    else if (type == "passenger")
    {
        Passenger *new_pass = new Passenger(username);
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