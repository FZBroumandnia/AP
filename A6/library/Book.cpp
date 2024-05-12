#include "Book.hpp"

int Book::fine_cost(int delayed_dates_count)
{
    if (delayed_dates_count <= 7)
        return (delayed_dates_count * BOOK_FIRST_7);
    else if (delayed_dates_count <= 21)
        return ((delayed_dates_count - 7) * BOOK_NEXT_14) + 7 * BOOK_FIRST_7;
    else
        return ((delayed_dates_count - 21) * BOOK_REMAIN_FINE) + 7 * BOOK_FIRST_7 + 14 * BOOK_NEXT_14;
};

int Book::loan_period()
{
    return BOOK_RPERIOD;
}