#ifndef _PERSON_HPP
#define _PERSON_HPP
#include <iostream>
#include <vector>
#include "Borrow_note.hpp"
#include "Document.hpp"
#include "Const.hpp"

class Person
{
public:
    Person(std::string _name) { name = _name; };
    std::string get_name() { return name; };
    virtual void borrow(Document *doc, int day);
    void extend(std::string title, int current_day);
    void person_return(std::string title, int current_day);
    int total_fine_cost(int day);

protected:
    std::vector<Borrow_note> borrow_list;

private:
    std::string name;
    int fine_cost = 0;
};

#endif