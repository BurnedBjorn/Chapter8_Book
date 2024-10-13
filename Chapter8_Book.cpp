// Chapter8_Book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
int to_int(Month m)
{
    return static_cast<int>(m);
}

Month operator++(Month& m) // prefix increment operator
{
    m = (m == Month::dec) ? Month::jan : static_cast<Month>(to_int(m) + 1); // "wrap around"
    return m;
}
vector<string> month_tbl = { "Not a month", "January", "February", "March", "April","May","June","July","August","September","October","November","December" };
ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[to_int(m)];
}

class Date {
public:
    class invalid { };
    Date(int d, Month m, int y);
    Date():d{1},y{2000},m{Month::jan}{}
    bool is_valid();
    void add_day(int n);
    int day() const { return d; }
    Month month() const { return m; }
    int year() const { return y; }
    bool IsLeapYear() {
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
bool Date::is_valid() {

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
            if (IsLeapYear) {
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

ostream& operator<<(ostream& os, Date& Date) {
    return os << Date.day() << ", " << Date.month() << ", " << Date.year();
}



class book
{
public:
    book(string t, string a, string n, Date d) :title{ t }, author{ a }, copyright{ d } {
        if (n.size() != 4) { error(n + ": not 4 digits, incorrect ISBN form"); }
        for (int i = 0; i < 3; i++)
        {
            if (!isdigit(n[i]))
            {
                error(n + ": incorrect ISBN form.");
            }
        }
        if (!isalpha(n[4])) { error(n + ": incorrect ISBN form"); }
    };
	~book();
    string get_ISBN() const { return ISBN; }
    string get_title() const { return title; }
    string get_author() const { return author; }
    Date get_copyright() const { return copyright; }
    bool get_status() const { return status; }
private:
    bool is_valid();
    string ISBN;
	string title;
	string author;
    Date copyright;
    bool status;
};



book::~book()
{
}

bool book::is_valid()
{
    return false;
}


int main()
{
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
