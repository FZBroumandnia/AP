#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "../server/server.hpp"
#include "../backend/UTaxi.hpp"
#include "../backend/Exception_handler.hpp"
#include "../backend/Consts.hpp"
#include "../backend/Trip.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

class signup_handler : public TemplateHandler
{
public:
  signup_handler(std::string filePath, UTaxi *_utaxi_p);
  std::map<std::string, std::string> handle(Request *req);

private:
  UTaxi *utaxi_p;
};

class post_trip_handler : public TemplateHandler
{
public:
  post_trip_handler(std::string filePath, UTaxi *_utaxi_p);
  std::map<std::string, std::string> handle(Request *req);

private:
  UTaxi *utaxi_p;
};

class delete_trip_handler : public TemplateHandler
{
public:
  delete_trip_handler(std::string filePath, UTaxi *_utaxi_p);
  std::map<std::string, std::string> handle(Request *req);

private:
  UTaxi *utaxi_p;
};

class trip_list_handler : public RequestHandler
{
public:
  trip_list_handler(UTaxi *_utaxi_p) : utaxi_p(_utaxi_p){};
  Response *callback(Request *);

private:
  UTaxi *utaxi_p;
};

#endif
