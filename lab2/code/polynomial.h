/*************************
 * Class Polynomial       *
 * TNG033: Lab 2          *
 **************************/

#pragma once

#include <iostream>
#include <vector>
#include "expression.h"
#include <cmath>
#include <format>
#include <iomanip>

class Polynomial : public Expression {
    // ADD CODE

public:

    Polynomial(double d);
    Polynomial(const std::vector<double>& v);
    Polynomial(const Polynomial& p);
    double operator()(double x) const override;
    Polynomial& operator+=(const Polynomial& x);
    friend Polynomial operator+(Polynomial x, const Polynomial& y);
    const Polynomial operator+(double x);
    const double operator[](int i) const;
    double& operator[](int i);
    Polynomial& operator=(const Polynomial& rhs);
    explicit operator std::string() const override;

    
    Polynomial* clone() const override {
        return new Polynomial{ *this };
    }
    virtual ~Polynomial() {}

private:
    std::vector<double> poly;
};



/*
 * std::vector should be used to store polinomial's coefficients
 */