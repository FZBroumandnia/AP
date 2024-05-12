#ifndef _BORROW_NOTE_HPP
#define _BORROW_NOTE_HPP
#include <iostream>
#include "Document.hpp"
#include "Const.hpp"

class Borrow_note
{
public:
    Borrow_note(int _borrow_day, Document *_doc);

    std::string get_title() { return doc_title; }
    void check_already_borrowed();
    int calculate_fine_cost(int current_day);
    void return_document(int current_day);
    void extend(int current_day);

private:
    std::string doc_title;
    Borrow_dates date;
    bool returned = false;
    int renewal_count = 0;
    int fine_cost = 0;
    Document *doc;
};

#endif