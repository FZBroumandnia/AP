#include "Library.hpp"

#include <string>
#include <cctype>
#include <algorithm>

void Library::check_empty_field(std::string input)
{
    bool empty = false;
    if (input.empty() || std::all_of(input.begin(), input.end(), [](char c)
                                 { return std::isspace(c); }))
    {
        empty = true;
    }
    if(empty)
    {
        std::cerr << EMPTY_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
}
bool Library::check_unique_member(std::string name)
{
    if (find_member(name))
    {
        std::cerr << UNIQUE_MEMBER_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    return true;
}

bool Library::check_unique_doc(std::string title)
{
    if (find_doc(title))
    {
        std::cerr << UNIQUE_DOCUMENT_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    return true;
}

void Library::add_student_member(std::string student_id, std::string student_name)
{
    check_empty_field(student_id);
    check_empty_field(student_name);
    if (check_unique_member(student_name))
    {
        Student *new_member = new Student(student_name, stoi(student_id));
        members.push_back(new_member);
    }
}

void Library::add_prof_member(std::string prof_name)
{
    check_empty_field(prof_name);
    if (check_unique_member(prof_name))
    {
        Professor *new_prof = new Professor(prof_name);
        members.push_back(new_prof);
    }
}

void Library::add_book(std::string book_title, int copies)
{
    check_empty_field(book_title);
    if (check_unique_doc(book_title))
    {
        Book *new_doc = new Book(book_title, copies);
        documents.push_back(new_doc);
    }
}

void Library::add_reference(std::string reference_title, int copies)
{
    check_empty_field(reference_title);
    if (check_unique_doc(reference_title))
    {
        Reference *new_reference = new Reference(reference_title, copies);
        documents.push_back(new_reference);
    }
}

void Library::add_magazine(std::string magazine_title, int year, int number, int copies)
{
    check_empty_field(magazine_title);
    if (number <= 0)
    {
        std::cerr << NUMBER_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (year <= 0)
    {
        std::cerr << YEAR_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (check_unique_doc(magazine_title))
    {
        Magazine *new_magazine = new Magazine(magazine_title, copies, year, number);
        documents.push_back(new_magazine);
    }
}

void Library::borrow(std::string member_name, std::string document_title)
{
    Document *doc = find_doc(document_title);
    if (!doc || !doc->is_available())
    {
        std::cerr << NO_DOC_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    Person *member = find_member(member_name);
    member->borrow(doc, current_day);
}

void Library::return_document(std::string member_name, std::string document_title)
{
    Person *member = find_member(member_name);
    member->person_return(document_title, current_day);
}

void Library::extend(std::string member_name, std::string document_title)
{
    Person *member = find_member(member_name);
    member->extend(document_title, current_day);
}

int Library::get_total_penalty(std::string member_name)
{
    Person *member = find_member(member_name);
    return member->total_fine_cost(current_day);
}

std::vector<std::string> Library::available_titles()
{
    std::vector<std::string> available_titles;
    for (Document *doc : documents)
    {
        if (doc->is_available())
            available_titles.push_back(doc->get_title());
    }
    return available_titles;
}

void Library::time_pass(int days)
{
    if (days < 0)
    {
        std::cerr << DAY_ERR << std::endl;
        exit(EXIT_SUCCESS);
    }
    current_day += days;
}

Person *Library::find_member(std::string name)
{
    for (Person *member : members)
    {
        if (member->get_name() == name)
            return member;
    }
    return NULL;
}

Document *Library::find_doc(std::string title)
{
    for (Document *doc : documents)
    {
        if (doc->get_title() == title)
            return doc;
    }
    return NULL;
}
