#ifndef _PROFESSOR_HPP
#define _PROFESSOR_HPP

#include <iostream>
#include <vector>
#include "Person.hpp"
#include "Document.hpp"
#include "Const.hpp"

class Professor : public Person
{
public:
    Professor(std::string name) : Person(name){};
    void borrow(Document *doc, int day);
};
#endif