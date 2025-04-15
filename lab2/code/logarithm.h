/*************************
 * Class Logarithm        *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <cmath>
#include "expression.h"
#include "polynomial.h"

class Logarithm : public Expression {
    // ADD CODE
public:

    Logarithm();
    Logarithm(const Expression& e, const double c1, const double c2, const int b);
    Logarithm(const Logarithm& l);
    double operator()(double d) const override;
    Logarithm& operator=(const Logarithm& l);
    Logarithm set_base(int b);
    explicit operator std::string() const override;

    Logarithm* clone() const override {
        return new Logarithm{ *this };
    }

    virtual ~Logarithm() {
        delete ptr_exp;
        c1 = 0.0;
        c2 = 0.0;
        base = 0;
    }

private:
    double c1;
    double c2;
    int base;
    Expression* ptr_exp;
};
