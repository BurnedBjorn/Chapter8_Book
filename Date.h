#pragma once
#include "std_lib_facilities.h"


enum class Month {
    jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
static int to_int(Month m);


static Month operator++(Month& m); // prefix increment operator

vector<string> month_tbl = { "Not a month", "January", "February", "March", "April","May","June","July","August","September","October","November","December" };
static ostream& operator<<(ostream& os, Month m);
enum class Day;

class Date;
static ostream& operator<<(ostream& os, Date& Date); 