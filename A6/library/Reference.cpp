#include "Reference.hpp"

int Reference::fine_cost(int delayed_dates_count)
{
    if (delayed_dates_count <= 3)
        return (delayed_dates_count * REFERENCE_FIRST_3);
    else
        return ((delayed_dates_count - 3) * REFERENCE_REMAIN_FINE) + 3 * REFERENCE_FIRST_3;
};
int Reference::loan_period()
{
    return REFERENCE_PERIOD;
}