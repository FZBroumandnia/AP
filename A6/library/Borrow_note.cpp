#include "Borrow_note.hpp"

Borrow_note::Borrow_note(int _borrow_day, Document *_doc)
{
    doc = _doc;
    date.issue_date = _borrow_day;
    date.expiry_date = doc->loan_period() + date.issue_date;
    doc_title = doc->get_title();
}

int Borrow_note::calculate_fine_cost(int current_day)
{
    if (!returned)
    {
        if (current_day > date.expiry_date)
            fine_cost = doc->fine_cost(current_day - date.expiry_date);
    }
    return fine_cost;
}

void Borrow_note::check_already_borrowed()
{
    if (!returned)
    {
        std::cerr << BORROWED_ALLREADY << std::endl;
        exit(EXIT_SUCCESS);
    }
}

void Borrow_note::return_document(int current_day)
{
    returned = true;
    doc->returned();
    if (current_day > date.expiry_date)
        fine_cost = doc->fine_cost(current_day - date.expiry_date);
    date.return_date = current_day;
}

void Borrow_note::extend(int current_day)
{
    if (current_day == date.issue_date)
    {
        std::cerr << SAME_BORROW_EXTEND << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (current_day > date.expiry_date)
    {
        std::cerr << EXTEND_AFTER_EXPIRE << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (renewal_count >= 2)
    {
        std::cerr << TWO_TIMES_RENEW << std::endl;
        exit(EXIT_SUCCESS);
    }
    date.expiry_date += doc->renew_period();
    renewal_count++;
}