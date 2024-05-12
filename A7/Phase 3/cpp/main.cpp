#include "handlers.hpp"
#include "my_server.hpp"
#include "../backend/UTaxi.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  while (true)
  {
    try
    {
      UTaxi *utaxi = new UTaxi(argv[1]);
      MyServer server(5000);
      
      server.setNotFoundErrPage("static/404.html");

      server.get("/odd.jpg", new ShowImage("pic/odd.jpg"));
      server.get("/who", new ShowImage("pic/who.png"));
      server.get("/night", new ShowImage("pic/night.png"));
      server.get("/day", new ShowImage("pic/day.png"));
      server.get("/delete", new ShowImage("pic/de.png"));

      server.get("/home.css", new ShowFile("css/home.css", "text/css"));
      server.get("/table.css", new ShowImage("css/table.css"));
      server.get("/delete_trip.css", new ShowFile("css/delete_trip.css", "text/css"));
      server.get("/post_trip.css", new ShowFile("css/post_trip.css", "text/css"));
      server.get("/signup.css", new ShowFile("css/signup.css", "text/css"));

      server.get("/", new ShowPage("static/home.html"));
      server.get("/post_trip", new post_trip_handler("template/post_trip.html", utaxi));
      server.get("/delete_trip", new delete_trip_handler("template/delete_trip.html", utaxi));
      server.get("/signup", new signup_handler("template/signup.html", utaxi));
      server.get("/triplistsign", new ShowPage("static/trip_list_sign.html"));
      server.get("/trip_list", new trip_list_handler(utaxi));
      server.post("/trip_list", new trip_list_handler(utaxi));

      server.run();
    }
    catch (Server::Exception e)
    {
      cerr << e.getMessage() << endl;
    }
  }
}
