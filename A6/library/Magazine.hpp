#ifndef _MAGAZINE_HPP
#define _MAGAZINE_HPP
#include <iostream>
#include "Document.hpp"
#include "Const.hpp"

class Magazine : public Document
{
public:
    Magazine(std::string name, int copies, int _year, int _number);
    ;
    int fine_cost(int delayed_dates_count);
    int loan_period();
    int renew_period();

private:
    int year;
    int number;
};

#endif