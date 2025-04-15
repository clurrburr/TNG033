/*******************************
 * Lab 3: exercise 2            *
 * Polynomial class             *
 *******************************/
#pragma once
#include "polynomial.h"
#include <algorithm>

Polynomial::Polynomial(int coeff, int exp) {
	if (coeff != 0) {
		coefficients_table[exp] = coeff;
	}
}
//copying poly to coefficients_table from the back
Polynomial::Polynomial(const std::vector<std::pair<int, int>>& poly) {
	std::copy(poly.begin(), poly.end(), std::inserter(coefficients_table, coefficients_table.end()));
}
Polynomial& Polynomial::operator+=(const Polynomial& rhs) {
	for (auto it = rhs.coefficients_table.begin(); it != rhs.coefficients_table.end(); it++) {
		//coeff + coeff
		coefficients_table[it->first] += it->second;
		if (coefficients_table[it->first] == 0) {
			//delete terms with the coefficient zero
			coefficients_table.erase(it->first);
		}
	}
	return *this;
}
Polynomial& Polynomial::operator-=(const Polynomial& rhs) {
	for (auto it = rhs.coefficients_table.begin(); it != rhs.coefficients_table.end(); it++) {
		coefficients_table[it->first] -= it->second;
		if (coefficients_table[it->first] == 0) {
			coefficients_table.erase(it->first);
		}
	}
	return *this;
}
Polynomial& Polynomial::operator*=(const Polynomial& rhs) {
	Polynomial result;
	for (auto it = coefficients_table.begin(); it != coefficients_table.end(); it++) {
		 result += rhs.multPoly(*it);
	}
	*this = result;
	return *this;
}
Polynomial Polynomial::multPoly(const Term& t) const{
		Polynomial result;
		for (auto it = coefficients_table.begin(); it != coefficients_table.end(); it++) {
			int degree = t.first + it->first;
			int coeff = t.second * it->second;
			result.coefficients_table[degree] = coeff;
		}
		return result;
}
Polynomial::operator std::string() const{
	std::string result = "";
	char sign;
	if (coefficients_table.empty()) {
		return std::string("0");
	}
	for (auto it = coefficients_table.begin(); it != coefficients_table.end(); it++) {
		int exp = it->first;
		int coeff = it->second;
		if (it == coefficients_table.begin()) {
				result += std::format("{}X^{}", coeff, exp);
		}
		else {
			sign = '+';
			if (coeff < 0) {
				sign = '-';
			}
			result += std::format(" {} {}X^{}", sign, std::abs(coeff), exp);
		}
	}
	return result;
}
int Polynomial::degree() const{
	if (coefficients_table.empty()) {
		return 0;
	}
	else {
		auto it = coefficients_table.rbegin(); //reversed begin, end is an empty slot
		return it->first;
	}
}
