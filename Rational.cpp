#include "std_lib_facilities.h"
class Rational
{
public:
	Rational();
	~Rational();
	int get_num() { return numerator; }
	int get_den() { return denominator; }
	double to_double() { if (denominator != 0) { return numerator / denominator; }else{} }
private:
	int numerator = 0;
	int denominator = 1;
};

Rational::Rational()
{
}

Rational::~Rational()
{
}