#ifndef _REFERENCE_HPP
#define _REFERENCE_HPP
#include <iostream>

#include "Document.hpp"
#include "Const.hpp"

class Reference : public Document
{
public:
    Reference(std::string name, int copies) : Document(name, copies){};
    int fine_cost(int delayed_dates_count);
    int loan_period();
};

#endif