#ifndef _STUDENT_HPP
#define _STUDENT_HPP
#include <iostream>
#include <vector>
#include "Person.hpp"
#include "Document.hpp"
#include "Const.hpp"

class Student : public Person
{
public:
    Student(std::string name, int _std_id) : Person(name) { std_id = _std_id; };
    void borrow(Document *doc, int day);

private:
    int std_id;
};


#endif