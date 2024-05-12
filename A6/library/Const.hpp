#ifndef _CONST_HPP
#define _CONST_HPP

#include <iostream>
const int MAX_BORROW_STD = 2;
const int MAX_BORROW_PROF = 5;

enum loan_period
{
    BOOK_RPERIOD = 10,
    MAGAZINE_PERIOD = 2,
    REFERENCE_PERIOD = 5,
};

enum fine_costs
{
    BOOK_FIRST_7 = 2000,
    BOOK_NEXT_14 = 3000,
    BOOK_REMAIN_FINE = 5000,
    REFERENCE_FIRST_3 = 5000,
    REFERENCE_REMAIN_FINE = 7000,
    MAG_BEFORE_90 = 2000,
    MAG_AFTER_90 = 3000,
};
struct Borrow_dates
{
    int issue_date;
    int expiry_date;
    int return_date;
};

const std::string DAY_ERR = "Invalid day";
const std::string NUMBER_ERR = "Invalid number";
const std::string YEAR_ERR = "Invalid year";
const std::string EMPTY_ERR = "Empty field";
const std::string BORROWED_ALLREADY = "You borrowed this document already";
const std::string NOT_BORROWED = "You have not borrowed this document";
const std::string RENEW_MAG_ERR = "You can't renew magazines";
const std::string SAME_BORROW_EXTEND = "You can't extend and borrow a document on the same day";
const std::string EXTEND_AFTER_EXPIRE = "You can't renew a document after receiving a penalty";
const std::string TWO_TIMES_RENEW = "You can't renew a document more than two times";
const std::string UNIQUE_MEMBER_ERR = "Name already exists";
const std::string UNIQUE_DOCUMENT_ERR = "A document with the specified name already exists";
const std::string MAX_BORROW_ERR = "Maximum number of allowed borrows exceeded";
const std::string NO_DOC_ERR = "This document does not exist";

#endif