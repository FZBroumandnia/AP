#include "Student.hpp"

void Student::borrow(Document *doc, int day)
{
    if (borrow_list.size() >= MAX_BORROW_STD)
    {
        std::cerr << MAX_BORROW_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    Person::borrow(doc, day);
}