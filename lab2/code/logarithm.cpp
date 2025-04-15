/*********************************************************
 * Class Logarithm member functions implementation        *
 * TNG033: Lab 2                                          *
 **********************************************************/

#include <cassert>
#include "logarithm.h"

Logarithm::Logarithm(){
	base = 2;
	c1 = 0.0;
	c2 = 1.0;
	std::vector<double> v = { 0, 1 };
	ptr_exp = new Polynomial {v};
}
Logarithm::Logarithm(const Expression& e, const double d1, const double d2, const int b) : c1{ d1 }, c2{ d2}, base{b}, ptr_exp{ e.clone() }{
	assert(b > 1);
	/*if (b > 1) {
		c1 = d1;
		c2 = d2;
		base = b;
		ptr_exp = e.clone();
	}*/
}
Logarithm::Logarithm(const Logarithm& l){
	c1 = l.c1;
	c2 = l.c2;
	base = l.base;
	ptr_exp = l.ptr_exp->clone(); //Uses the virtual function clone to determine what 
}								  // kind of expression is being copied. Cannot use a
								  // copy constructor since they can't be virtual
double Logarithm::operator()(double d) const{
	return c1 + c2 * log((*ptr_exp)(d))/log(base);
}

Logarithm& Logarithm::operator=(const Logarithm& l) {
	c1 = l.c1;
	c2 = l.c2;
	base = l.base;
	delete ptr_exp;
	ptr_exp = l.ptr_exp->clone();

	return *this;
}

Logarithm Logarithm::set_base(int b) {
	base = b;
	return *this;
}
Logarithm::operator std::string() const{
	std::string result = "";
	char sign = '+';
	if (c2 < 0) {
		sign = '-';
	}
	result = std::format("{:.2f} {} {:.2f} * Log_{}( {} )", c1, sign, std::abs(c2), base, std::string(*ptr_exp));

	return result;
}


// ADD implementation of the member functions for class Logarithm
