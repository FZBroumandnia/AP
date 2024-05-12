#ifndef _BOOK_HPP
#define _BOOK_HPP
#include <iostream>
#include "Document.hpp"
#include "Const.hpp"

class Book : public Document
{
public:
    Book(std::string name, int copies) : Document(name, copies){};
    int fine_cost(int delayed_dates_count);
    int loan_period();
};

#endif