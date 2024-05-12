#include "Person.hpp"

void Person::borrow(Document *doc, int day)
{
    for (Borrow_note bp : borrow_list)
    {
        if (doc->get_title() == bp.get_title())
            bp.check_already_borrowed();
    }
    doc->borrowed();
    borrow_list.push_back(Borrow_note(day, doc));
}

void Person::extend(std::string title, int current_day)
{
    for (int i = 0; i < borrow_list.size(); i++)
    {
        if (title == borrow_list[i].get_title())
        {
            borrow_list[i].extend(current_day);
            return;
        }
    }
    std::cerr << NOT_BORROWED << std::endl;
    exit(EXIT_SUCCESS);
}

void Person::person_return(std::string title, int current_day)
{
    for (int i = 0; i < borrow_list.size(); i++)
    {
        if (title == borrow_list[i].get_title())
        {
            borrow_list[i].return_document(current_day);
            return;
        }
    }
    std::cerr << NOT_BORROWED << std::endl;
    exit(EXIT_SUCCESS);
}

int Person::total_fine_cost(int day)
{
    for (Borrow_note bp : borrow_list)
    {
        fine_cost += bp.calculate_fine_cost(day);
    }
    return fine_cost;
}