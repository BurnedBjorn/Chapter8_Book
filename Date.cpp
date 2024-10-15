#include "Date.h"
static int to_int(Month m)
{
    return static_cast<int>(m);
}
static Month operator++(Month& m) // prefix increment operator
{
    m = (m == Month::dec) ? Month::jan : static_cast<Month>(to_int(m) + 1); // "wrap around"
    return m;
}
static ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[to_int(m)];
}
enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};
class Date {
public:
    class invalid { };
    Date(int d, Month m, int y);
    Date() :d{ 1 }, y{ 2000 }, m{ Month::jan } {}
    bool is_valid() const;
    void add_day(int n);
    int day() const { return d; }
    Month month() const { return m; }
    int year() const { return y; }
    bool IsLeapYear() const {
        if (y % 4) {
            return true;
        }
        else {
            return false;
        }
    }
private:
    int d, y;
    Month m;
};
bool Date::is_valid() const {

    if ((d > 31) or (d < 1)) {
        return false;
    }
    switch (m)
    {
    case Month::feb:
        if (!IsLeapYear()) {
            if (d < 28) { return false; }
        }
        else {
            if (d < 29) { return false; }
        }
        break;
    case Month::apr:

    case Month::jun:

    case Month::sep:

    case Month::nov:
        if ((d < 1) or (d > 30)) {
            return false;
        }
        break;
    default:
        break;
    }
    return true;
}
Date::Date(int yy, Month mm, int dd) :y{ yy }, m{ mm }, d{ dd }
{
    // if (!is_valid()) {throw invalid{};}
}
void Date::add_day(int n) {
    if (n < 0) {
        cout << "negative add day not implemented\n";
        return;
    }
    d += n;

    while (true) {
        switch (m)
        {
        case Month::jan:
        case Month::mar:
        case Month::may:
        case Month::jul:
        case Month::aug:
        case Month::oct:

            if (d > 31)
            {
                d -= 31;
                ++m;
            }
            else {
                return;
            }
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            if (d > 30)
            {
                d -= 30;
                ++m;
            }
            else {
                return;
            }
            break;

        case Month::feb:
            if (IsLeapYear()) {
                if (d > 29)
                {
                    d -= 29;
                    ++m;
                }
                else {
                    return;
                }

            }
            else {
                if (d > 28)
                {
                    d -= 28;
                    ++m;
                }
                else {
                    return;
                }

            }
            break;
        case Month::dec:

            if (d > 31)
            {
                d -= 31;
                ++m;
                ++y;
            }
            else {
                return;
            }
            break;
        default:
            error("void Date::add_day(): invalid month");
            break;
        }
    }
}

static ostream& operator<<(ostream& os, Date& Date) {
    return os << Date.day() << ", " << Date.month() << ", " << Date.year();
}