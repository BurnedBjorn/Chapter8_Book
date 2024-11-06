// Chapter8_Book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"


class Rational
{
public:
    Rational() :numerator{ 1 }, denominator{ 1 } {};
    Rational(int n, int d) :numerator{ n }, denominator{ d } { if (d == 0) { error("\nno, you don't want to do division by 0, you're wrong\n"); } };
    ~Rational();
    int get_num() const { return numerator; }
    int get_den() const { return denominator; }
    void set_num(int n) { numerator = n; }
    void set_den(int d) {
        if (d!=0)
        {
            denominator = d;
        }
        else
        {
            error("\nno, you don't want to do division by 0, you're wrong\n");
        }
    }
    double to_double() { if (denominator != 0) { return numerator / denominator; } else { error("bruh"); } }
    Rational operator+(const Rational& other);
    Rational operator-(const Rational& other);
    Rational operator*(const Rational& other);
    Rational operator/(const Rational& other);
    Rational simplify(int num, int den);
    Rational simplify(const Rational& n);
    Rational simplify();
    
    
private:
    int numerator = 1;
    int denominator = 1;
};

Rational::~Rational()
{
}
Rational Rational::operator+(const Rational& other)
{
    Rational output;
    if (get_den()==other.get_den())
    {
        output = Rational{ get_num() + other.get_num(),get_den() };
    }
    else
    {
        output.set_den(get_den() * other.get_den());//common denominator
        output.set_num(get_num() * other.get_den() + other.get_num() * get_den());// calculate numerator
        
        //check if the fraction can be simplified
        
    }    
    return simplify(output.get_num(),output.get_den());
    
}
Rational Rational::operator-(const Rational& other)
{
    Rational negative{ other.get_num() * -1, other.get_den() };
    Rational self{ get_num(),get_den() };// should probably be done some other way
    return (self + negative);
}
Rational Rational::operator*(const Rational& other)
{
    Rational output{ get_num() * other.get_num(),get_den() * other.get_den() };
    return simplify(output);
}
Rational Rational::operator/(const Rational& other)
{
    if (other.get_num()==0)
    {
        error("trying to divide by 0");
    }
    Rational output{ get_num() * other.get_den(),get_den() * other.get_num() };
    return simplify(output);
}
Rational Rational::simplify(int num, int den)
{
    
    for (int i = 2; i < 11; i++)
    {
        while (den % i == 0 and num % i == 0)
        {
            den /= i;
            num /= i;
            //cout << i << endl;
        }
    }
    for (int i = 2; (i < abs(den)) and (i < abs(num)); i = i * 6 - 1)
    {
        while (den % i == 0 and num % i == 0)
        {
            den /= i;
            num /= i;
            //cout << i << endl;
        }
    }
    for (int i = 3; (i < abs(den)) and (i < abs(num)); i = i * 6 - 1)
    {
        while (den % i == 0 and num % i == 0)
        {
            den /= i;
            num /= i;
            // cout << i << endl;
        }
    }
    for (int i = 2; (i < abs(den)) and (i < abs(num)); i = i * 6 + 1)
    {
        while (den % i == 0 and num % i == 0)
        {
            den /= i;
            num /= i;
            //cout << i << endl;
        }
    }
    for (int i = 3; (i < abs(den)) and (i < abs(num)); i = i * 6 + 1)
    {
        while (den % i == 0 and num % i == 0)
        {
            den /= i;
            num /= i;
            //cout << i << endl;
        }
    }
    
    return Rational{ num,den };
}
Rational Rational::simplify(const Rational& n)
{
    return simplify(n.get_num(),n.get_den());
}
Rational Rational::simplify()
{
    return simplify(get_num(),get_den());
}


class Currency
{
public:
    Currency(string n, double er, char s) :name{ n }, exchange_rate{ er }, symbol{ s } {};
    ~Currency() {};
    string get_name() const { return name; }
    double get_rate() const { return exchange_rate; }
    char get_symbol() const { return symbol; }

private:
    string name;
    double exchange_rate = 1;
    char symbol;
};


class Money
{
public:
    


    Money() :cents{ 0 } {};
    Money(double n) { cents = input(n); };
    Money(double n, Currency c) :curr{ c } { cents = input(n); };
    ~Money();
    long int input(double n) {
        return static_cast<long int>(floor(n * 100 + 0.5))/curr.get_rate();
    }
    void set(double n) { cents = input(n); }
    void set_cents(long int n) { cents = n; }
    void set_currency(Currency c) { curr = c; }
    long int get_cents() const { return cents; }
    Currency get_curr() const { return curr; }
    double output() const {return curr.get_rate()* (static_cast<double>(cents) / 100.0); }
    Money operator+(const Money& other);
    Money operator-(const Money& other);
    bool operator!=(const Money& other);
    bool operator==(const Money& other);
    Money operator/(const double& other);
    Money operator*(const double& other);
    bool operator==(const double& other);
    bool operator!=(const double& other);
    bool operator<(const double& other);
    bool operator>(const double& other);
    Money& operator=(double value);

    vector<Currency> currency_list{ Currency{"dollar", 1, '$'} };

private:
    long int cents = 0;
    Currency curr{ "USD", 1, '$' };
};
Money Money::operator+(const Money& other)
{
    Money output;
    output.set_cents(get_cents() + other.get_cents());
    return output;
}

Money Money::operator-(const Money& other)
{
    Money output;
    output.set_cents(get_cents() - other.get_cents());
    return output;
}

Money Money::operator/(const double& other)
{
    if (other==0)
    {
        error("division by 0");
    }
    Money output;
    output.set_cents(static_cast<long int>(round(get_cents() / other)));
    return output;
}

Money Money::operator*(const double& other)
{
    Money output;
    output.set_cents(static_cast<long int>(round(get_cents() * other)));
    return output;
}

bool Money::operator==(const Money& other)
{
    return get_cents()==other.get_cents();
}

bool Money::operator==(const double& other)
{
    return output()==other;
}

bool Money::operator!=(const double& other)
{
    return output() != other;
}


bool Money::operator!=(const Money& other)
{
    return get_cents() != other.get_cents();
}

bool Money::operator<(const double& other)
{
    return output() < other;
}

bool Money::operator>(const double& other)
{
    return output() < other;
}

Money& Money::operator=(double value)
{
    set(value);
    return *this;
}

Money::~Money()
{
}
istream& operator>>(istream& is, Money& m) {
    double n;
    if (is >> n) {
        m.set(n);
    }
    else
    {
        is.clear();
        error("Money: bad input");
    }
    return is;
}
static ostream& operator<<(ostream& os, const Money& m) {
    return os << m.get_curr().get_symbol() << m.output();
}
static ostream& operator<<(ostream& os, const Rational& rat) {
    return os << rat.get_num() << "/" << rat.get_den();
}


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
    int century() const { return static_cast<int>(floor(year() / 100)+1); }
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
            if (d > 28) { return false; }//fixed
        }
        else {
            if (d > 29) { return false; }
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
        cout << yy << " " << mm << " " << dd << " ";
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
    Day wd = dt.weekday();
    doy -= to_int(wd); //get to the monday of the week
    
    
    Day j1wd = Date{ dt.year(),Month::jan, 1 }.weekday();//week day of jan 1
    int d = 7 - to_int(j1wd); //amount of days until the second monday of the year

    return ((doy-d+6)/7)+1;
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
    try {
        Money m{12.44};
        
        cin >> m;
        Money a = m;
        a = a / 0;
        cout << a;
    }
    catch (exception& e) {
        cerr << "exception: " << e.what() << endl;
        char c;
        while (cin >> c && c != ';');
        return 1;
    }
    catch (...) {
        cerr << "exception\n";
        //char c;
        //while (cin >> c && c != ';');
        return 2;
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

