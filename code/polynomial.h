/*******************************
 * Lab 3: exercise 2            *
 * Polynomial class             *
 * Header file                  *
 *******************************/
#include <vector>
#include <iostream>
#include <string>
#include <utility> // std::pair
#include <map>
#include <format>

class Polynomial {
public:
	using Term = std::pair<int, int>;
	Polynomial(int coeff = 0, int exp = 0);
	// explicit Polynomial(const std::vector<std::pair<int, int>>& poly);
	explicit Polynomial(const std::vector<Term>& poly);
	Polynomial(const Polynomial& rhs) = default;
	Polynomial& operator+=(const Polynomial& rhs);
	Polynomial& operator-=(const Polynomial& rhs);
	Polynomial& operator*=(const Polynomial& rhs);
	Polynomial& operator=(const Polynomial& rhs) = default;

	friend Polynomial operator+(Polynomial lhs, const Polynomial& rhs){
		lhs += rhs;
		return lhs;
	}
	friend Polynomial operator-(Polynomial lhs, const Polynomial& rhs) {
		lhs -= rhs;
		return lhs;
	}
	friend Polynomial operator*(Polynomial lhs, const Polynomial& rhs) {
		lhs *= rhs;
		return lhs;
	}
	friend bool operator==(const Polynomial& lhs, const Polynomial& rhs) {
		return lhs.coefficients_table == rhs.coefficients_table;
	}
	friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs) {
		os << std::string(rhs);
		return os;
	}
	int degree() const;
	explicit operator std::string() const;

	~Polynomial() = default;

private:
	std::map<int, int>coefficients_table;
	Polynomial multPoly(const Term& t) const; 
};