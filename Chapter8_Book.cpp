// Chapter8_Book.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "std_lib_facilities.h"
#include "Date.h"

class book
{
public:
    enum class genre {
        fiction, nonfiction, periodical, biography, children, unset
    };

    book(string t, string a, genre g, string n, Date d) :title{ t }, author{ a }, genre{ g }, copyright{ d } {
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
    book():title{"default"}, author{"default"}, genre{genre::unset}, ISBN{"000a"}, copyright{}{}
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
