#include "handlers.hpp"

using namespace std;

string make_error_response(Exception_handler ex)
{
  ostringstream body;
  body << "<html>" << endl
       << "  <body style='text-align: center;'> " << endl
       << "     <div<h1><a href='/'>UTaxi!</a></h1></div>" << endl
       << "<div><h1>" << endl;

  string msg = ex.error_message();
  body << msg
       << "   </h1></div>" << endl
       << "     </body></html>" << endl;
  return body.str();
}

string make_button(string username, string sorted_string, string id)
{
  ostringstream button;
  button << "                <td> <form action='/trip_list' method='post'> <input name= 'trip_id' value = '"
         << id
         << "' type = 'hidden' />" << endl
         << "<input name= 'username' value = '"
         << username
         << "' type = 'hidden'/>" << endl
         << "<input name= 'sorted' value = '"
         << sorted_string
         << "' type = 'hidden'/>" << endl;
  return button.str();
}

string make_table_header()
{
  ostringstream table_header;
  table_header << "<html>" << endl
               << "    <head><title>Trip List</title><link rel='stylesheet' type='text/css' href='/table.css'></head>" << endl
               << "    <body><section><div class='container'>" << endl
               << "      <div class = 'head'><img src='/day' style='width:100%; object-fit: cover;'></div>" << endl
               << "      <div class = 'title'><a href='/'>UTaxi!</a></div>" << endl
               << "        <div><table>" << endl
               << "            <tr>" << endl
               << "                <th>ID</th>" << endl
               << "                <th>Passenger Name</th>" << endl
               << "                <th>Origin</th>" << endl
               << "                <th>Destination</th>" << endl
               << "                <th>Cost</th>" << endl
               << "                <th>Status</th>" << endl
               << "                <th>&nbsp</th>" << endl
               << "          </tr>" << endl;
  return table_header.str();
}

string choose_button(Trip *trip, string username, string sorted_string)
{
  ostringstream datacell;
  datacell
      << make_button(username, sorted_string, trip->get_id()) << endl;
  if (trip->same_status(waiting))
    datacell << "<button type = 'submit' name = 'but' value ='accept'> Accept</button>" << endl;
  else if (trip->same_status(traveling) && trip->same_driver(username))
    datacell << "<button type = 'submit' name = 'but' value ='finish'> Finish</button>" << endl;

  return datacell.str();
}

string make_table_date_cell(Trip *trip, string username, string sorted_string)
{
  ostringstream datacell;
  if (!trip->same_status(Canceled))
  {
    datacell
        << "            <tr>" << endl
        << "                <td>" << trip->get_id() << "</td>" << endl
        << "                <td>" << trip->get_passenger() << "</td>" << endl
        << "                <td>" << trip->get_origin() << "</td>" << endl
        << "                <td>" << trip->get_destination() << "</td>" << endl
        << "                <td>" << trip->get_trip_cost() << "</td>" << endl
        << "                <td>" << trip->trip_status_string() << "</td>" << endl;
    datacell << choose_button(trip, username, sorted_string);
    datacell
        << "          </form></td></tr>" << endl;
    return datacell.str();
  }
}

string make_table_response(vector<Trip *> trips, string username, string sorted_string)
{
  ostringstream body;
  body << make_table_header();
  for (int i = 0; i < trips.size(); i++)
    body << make_table_date_cell(trips[i], username, sorted_string);
  body
      << "      </div></table>" << endl
      << "      </div></section></body>" << endl
      << "</html>" << endl;
  return body.str();
}

Response *trip_list_handler::callback(Request *req)
{
  string username = req->getBodyParam("username");
  string sorted_string = req->getBodyParam("sorted");
  string trip_id = req->getBodyParam("trip_id");
  string button_value = req->getBodyParam("but");

  Response *res = new Response;
  res->setHeader("Content-Type", "text/html");
  try
  {
    utaxi_p->handle_get(username);
    vector<Trip *> trips;
    if (sorted_string == "no")
      trips = utaxi_p->get_all_trips();
    else if (sorted_string == "yes")
      trips = utaxi_p->handle_sorted_trips();

    if (button_value == "accept")
      utaxi_p->post_accept(username, trip_id);
    if (button_value == "finish")
      utaxi_p->post_finish(username, trip_id);
    res->setBody(make_table_response(trips, username, sorted_string));
  }
  catch (Exception_handler ex)
  {
    res->setBody(make_error_response(ex));
  }
  return res;
}

post_trip_handler::post_trip_handler(string filePath, UTaxi *_utaxi_p) : TemplateHandler(filePath), utaxi_p(_utaxi_p) {}

map<string, string> post_trip_handler::handle(Request *req)
{
  string value = req->getQueryParam("but");
  string username = req->getQueryParam("username");
  string hurry_string = req->getQueryParam("hurry_");
  string destination = req->getQueryParam("destination");
  string origin = req->getQueryParam("origin");
  string directed = req->getQueryParam("directed");

  bool in_hurry;
  if (hurry_string == "yes")
    in_hurry = true;
  if (hurry_string == "no")
    in_hurry = false;

  map<string, string> context;
  try
  {
    if (directed == "yes")
    {
      if (value == "post")
      {
        utaxi_p->post_trips(username, origin, destination, in_hurry);
        string id;
        id += "Your trip id is: ";
        id += to_string(utaxi_p->get_trips_size());
        context["id"] = id;
      }
      if (value == "cost")
        context["id"] = to_string(utaxi_p->handle_cost(username, origin, destination, in_hurry));
    }
    else
      context["id"] = "";
  }
  catch (Exception_handler ex)
  {
    context["id"] = ex.error_message();
  }
  return context;
}

delete_trip_handler::delete_trip_handler(string filePath, UTaxi *_utaxi_p) : TemplateHandler(filePath), utaxi_p(_utaxi_p) {}

map<string, string> delete_trip_handler::handle(Request *req)
{
  string directed = req->getQueryParam("directed");
  map<string, string> context;
  try
  {
    if (directed == "yes")
    {
      utaxi_p->delete_trips(req->getQueryParam("username"), req->getQueryParam("id"));
      context["msg"] = "ok";
    }
    else
      context["msg"] = "";
  }
  catch (Exception_handler ex)
  {
    context["msg"] = ex.error_message();
  }
  return context;
}

signup_handler::signup_handler(string filePath, UTaxi *_utaxi_p) : TemplateHandler(filePath), utaxi_p(_utaxi_p) {}

map<string, string> signup_handler::handle(Request *req)
{
  string directed = req->getQueryParam("directed");

  map<string, string> context;
  try
  {
    if (directed == "yes")
    {
      utaxi_p->signup(req->getQueryParam("username"), req->getQueryParam("type_"));
      context["msg"] = "ok";
    }
    else
      context["msg"] = "";
  }
  catch (Exception_handler ex)
  {
    context["msg"] = ex.error_message();
  }
  return context;
}