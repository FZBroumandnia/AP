#include <iostream>
#include "Document.hpp"

Document::Document(std::string _name, int _copies)
{
    title = _name;
    total_copies = _copies;
    available_copies = total_copies;
}

bool Document::is_available()
{
    if (available_copies)
        return true;
    return false;
}
void Document::borrowed()
{
    available_copies--;
}
void Document::returned()
{
    available_copies++;
}

int Document::renew_period()
{
    return loan_period();
}