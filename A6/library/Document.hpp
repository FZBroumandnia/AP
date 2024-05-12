#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

#include <iostream>

class Document
{
public:
    Document(std::string _name, int _copies);
    std::string get_title() { return title; };

    bool is_available();
    void borrowed();
    void returned();
    virtual int fine_cost(int delayed_dates_count) = 0;
    virtual int loan_period() = 0;
    virtual int renew_period();

private:
    std::string title;
    int total_copies;
    int available_copies;
};

#endif
