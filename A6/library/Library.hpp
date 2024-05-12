#ifndef _LIBRARY_HPP
#define _LIBRARY_HPP
#include <iostream>
#include "Person.hpp"
#include "Student.hpp"
#include "Professor.hpp"
#include "Document.hpp"
#include "Book.hpp"
#include "Reference.hpp"
#include "Magazine.hpp"
#include "Borrow_note.hpp"

class Library
{
public:
    void add_student_member(std::string student_id, std::string student_name);
    void add_prof_member(std::string prof_name);
    void add_book(std::string book_title, int copies);
    void add_magazine(std::string magazine_title, int year, int number, int copies);
    void add_reference(std::string reference_title, int copies);
    void borrow(std::string member_name, std::string document_title);
    void extend(std::string member_name, std::string document_title);
    void return_document(std::string member_name, std::string document_title);
    int get_total_penalty(std::string member_name);
    std::vector<std::string> available_titles();
    void time_pass(int days);
    Person *find_member(std::string name);
    Document *find_doc(std::string title);
    bool check_unique_member(std::string name);
    bool check_unique_doc(std::string title);
    void check_empty_field(std::string input);

private:
    std::vector<Person *> members;
    std::vector<Document *> documents;
    int current_day = 0;
};
#endif