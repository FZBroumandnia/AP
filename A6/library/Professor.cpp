#include "Professor.hpp"
void Professor::borrow(Document *doc, int day)
{
    if (borrow_list.size() >= MAX_BORROW_PROF)
    {
        std::cerr << MAX_BORROW_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    Person::borrow(doc, day);
}