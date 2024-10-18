// Chapter8_Book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"

enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
static int to_int(Month m)
{
    return static_cast<int>(m);
}
static int to_int(double d)
{
    return static_cast<int>(d);
}
static Month operator++(Month& m) // prefix increment operator
{
    m = (m == Month::dec) ? Month::jan : static_cast<Month>(to_int(m) + 1); // "wrap around"
    return m;
}
vector<string> month_tbl = { "Not a month", "January", "February", "March", "April","May","June","July","August","September","October","November","December" };
static ostream& operator<<(ostream& os, Month m)
{
    return os << month_tbl[to_int(m)];
}

enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday, error
};
static int to_int(Day d) {
    return static_cast<int>(d);
}
vector<string> weekday_tbl = { "mon","tue","wed","thu","fri","sat","sun","error"};

static bool leapyear(int y) {
    if (y % 400 == 0)
    {
        return true;
    }
    if (y % 100 == 0)
    {
        return false;
    }
    if (y % 4 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

class Date {
public:
    class invalid { };
    
    Date(int d, Month m, int y);
    Date():d{1},y{2001},m{Month::jan}{}
    bool is_valid() const;
    void add_day(int n);
    int day() const { return d; }
    Month month() const { return m; }
    int year() const { return y; }
    bool IsLeapYear() const {
        return leapyear(year());
    }
    int century() const { return floor(year() / 100)+1; }
    Day weekday() const;
    int day_of_year() const;
private:
    int d, y;
    Month m;
};
static ostream& operator<<(ostream& os, const Day& day) {
    return os << weekday_tbl[to_int(day)];
}
static ostream& operator<<(ostream& os, Date& Date) {
    return os << Date.day() << ", " << Date.month() << ", " << Date.year();
}
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
    if (!is_valid())
    {
        error("invalid date");
    }
    
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

Day Date::weekday() const
{
    int yr = year() % 100;
    
    int mth = to_int(month()) - 2;
    if (mth<1)
    {
        mth += 12;
    }
    if (to_int(month())<=2)
    {
        yr -= 1;
    }
    int index = static_cast<int>(floor(day() + floor((2.6 * (mth)) - 0.2)-2*century()+yr+floor(yr/4)+floor(century()/4)));
    index = index % 7;
    if ((century()%4)==0)
    {
        index -= 1;
    }
    //cout <<"ce: "<< century() << ", yr: " << yr << ", mth: " << mth << ", index: " << index << endl;
    index += 1;
    while (index < 0)
    {
        //cout << index << endl;
        index += 7;
    }
    while (index >6)
    {
        //cout << index << endl;
        index -= 7;
    }
    
    
    if ((index>=0)and(index<7))
    {
        //cout << index << " day: ";
        return Day(index);
    }
    else
    {
        return Day::error;
    }
    
}

int Date::day_of_year() const
{
    int output = 0;
    Month m{ Month::jan };
    while (to_int(m)<to_int(month()))
    {
        switch (m)
        {
        case Month::jan:
        case Month::mar:
        case Month::may:
        case Month::jul:
        case Month::aug:
        case Month::oct:
            output += 31;
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            output += 30;
            break;

        case Month::feb:
            if (IsLeapYear()) {
                output += 29;

            }
            else {
                output += 28;

            }
            break;
        case Month::dec:

            output += 31;
        default:

            break;
        }
        ++m;
    }
        
    
    output += day();
    return output;
}

static Date next_workday(const Date& dt)
{
    Date output = dt;
    
    output.add_day(1);
    if (output.weekday()==Day::saturday)
    {
        output.add_day(2);
    }
    if (output.weekday()==Day::sunday)
    {
        output.add_day(1);
    }
    return output;
    
}


static int week_of_year(const Date& dt)//buggy
{
    int doy = dt.day_of_year();
    Day j1wd = Date{ dt.year(),Month::jan, 1 }.weekday();
    switch (j1wd)
    {
    case Day::monday:
        //doy -= 7;
        break;
    case Day::tuesday:
        doy -= 7;
        break;
    case Day::wednesday:
        doy -= 6;
        break;
    case Day::thursday:
        doy -= 5;
        break;
    case Day::friday:
        doy -= 4;
        break;
    case Day::saturday:
        doy -= 3;
        break;
    case Day::sunday:
        doy -= 2;
        break;
    case Day::error:
        break;
    default:
        break;
    }
    if (doy<1)
    {
        return 1;
    }
    else
    {
        return to_int(floor(doy / 7) + 1);
    }
}


class book
{
public:
    enum class genre {
        fiction, nonfiction, periodical, biography, children, unset
    };

    book(string t, string a, genre g, string n, Date d) :title{ t }, author{ a }, genre{ g }, copyright{ d }, status{ true } {
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
    book() :title{ "default" }, author{ "default" }, genre{ genre::unset }, ISBN{ "000a" }, copyright{}, status{ true } {}
    string get_ISBN() const { return ISBN; }

    string get_title() const { return title; }

    string get_author() const { return author; }

    genre get_genre() const { return genre; }

    Date get_copyright() const { return copyright; }

    bool get_status() const { return status; } // checked in - true. checked out - false

    void check_in() {
        if (status == false)
        {
            status = true; 
            return;
        }
        else {
            error("book checked in already");
        }
    }

    void check_out() {
        if (status == true)
        {
            status = false;
            return;
        }
        else {
            error("book checked out already");
        }
    }

    bool operator==(const book& other) const{
        return get_ISBN() == other.get_ISBN();
    }

    bool operator!=(const book& other) const{
        return get_ISBN() != other.get_ISBN();
    }

    
    
private:
    
    string ISBN;
	string title;
	string author;
    genre genre;
    Date copyright;
    bool status;
};
static ostream& operator<<(ostream& os, const book& book) {
    return os << book.get_title() << endl << book.get_author() << endl << book.get_ISBN() << endl;
}
book::~book()
{
}

class patron
{
public:
    patron(string name, int num) :username{ name }, card_number{ num }, fees{ 0 } {};
    patron() :username{ "default" } {}
    ~patron();
    void change_username(string new_name) { username = new_name; }
    string get_username() const { return username; }
    int get_card_number() const { return card_number; }
    bool has_fees() const { return fees > 0; }
    void add_fee(double amount) { fees += amount; }
    double payment(double amount);
    void clear_fees() { fees = 0; }
    bool operator==(const patron& other) const{
        return get_card_number() == other.get_card_number();
    }
private:
    string username;
    int card_number=0;
    double fees =0;

};
patron::~patron()
{
}
double patron::payment(double amount)
{
    fees -= amount;
    double change = 0;
    if (fees<0)
    {
        change = fees * -1;
        fees = 0;
    }
    return change;
}

class library
{
public:
    library();
    ~library();
    struct transaction //unfinished
    {
        transaction(book b, patron t, Date d) :book{ b }, user{ t }, date{ d } {};
        book book;
        patron user;
        Date date;
    };
    void add_book(book new_book);
    void add_user(patron new_user);
    bool validate_book(const book& b) const {
        if (find(books.begin(), books.end(), b) == books.end()) {
            return false;
        }
        else {
            return true;
        }
    }
    bool validate_user(const patron& p) const {
        if (find(users.begin(), users.end(), p) == users.end()) {
            return false;
        }
        else {
            return true;
        }
    }
    void add_transaction(const transaction& ta);
    void checkout_book(book book);
    vector<patron> indebted();
private:
    vector<patron> users;
    vector<book> books;
    vector<transaction> transactions;
};

library::library()
{
}

library::~library()
{
}

void library::add_book(book new_book)
{
    if (validate_book(new_book)) {
        books.push_back(new_book);
    }
    else {
        error(new_book.get_ISBN() + ": book already in library");
    }
}

void library::add_user(patron new_user)
{
    if (validate_user(new_user)) {
        users.push_back(new_user);
    }
    else {
        error(new_user.get_card_number() + ": user alredy exists");
    }
}

void library::add_transaction(const transaction& ta)
{
    if (!validate_book(ta.book))
    {
        error(ta.book.get_ISBN() + ": book doesn't exist");
    }
    if (ta.book.get_status())
    {
        error(ta.book.get_ISBN() + ": book is not in library");
    }
    if (!validate_user(ta.user))
    {
        error(ta.user.get_username() + ": user not in database");
    }
    if (ta.user.has_fees())
    {
        error(ta.user.get_username() + ": unpaid fees");
    }
    
    checkout_book(ta.book);
    transactions.push_back(ta);

}

void library::checkout_book(book book)
{

    int index = (find(books.begin(), books.end(), book) - books.begin());//i googled how to do it i dont' actira;ly undrtstna pointers
    books[index].check_out();
}

vector<patron> library::indebted() {
    vector<patron> output;
    for (int i = 0; i < users.size(); i++)
    {
        if (users[i].has_fees())
        {
            output.push_back(users[i]);
        }
    }
    return output;
}






int main()
{
    Date test{ 2023,Month::jan, 1 };
    for (int i = 0; i < 720; i++)
    {
       
        cout <<test<<", "<< test.day_of_year()<<", "<<test.weekday() << ", week num:" << week_of_year(test) << endl;
        test.add_day(1);

    }
    
    
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
