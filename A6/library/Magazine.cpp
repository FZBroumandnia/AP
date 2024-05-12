#include "Magazine.hpp"

Magazine::Magazine(std::string name, int copies, int _year, int _number) : Document(name, copies)
{
    year = _year;
    number = _number;
};
int Magazine::fine_cost(int delayed_dates_count)
{
    if (year < 1390)
        return (delayed_dates_count * MAG_BEFORE_90);
    else
        return (delayed_dates_count * MAG_AFTER_90);
};
int Magazine::loan_period()
{
    return MAGAZINE_PERIOD;
}
int Magazine::renew_period()
{
    std::cerr << RENEW_MAG_ERR << std::endl;
    exit(EXIT_SUCCESS);
    return 0;
}