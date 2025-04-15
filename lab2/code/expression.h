/*************************
 * Class Expression       *
 * TNG033: Lab 2          *
 **************************/

#pragma once
#include <iostream>
constexpr double Epsilon = 1.0e-5;

class Expression {
public:
    // Destructor
    virtual ~Expression() {
        --count_expressions;
    }

    // ADD OTHER MEMBER FUNCTIONS
    bool isRoot(double x) const;
    virtual double operator()(double d)const = 0;
    virtual Expression* clone()const = 0;
    //Different types of expressions can't be equal to each other
    Expression& operator=(const Expression& x) = delete;
    explicit virtual operator std::string() const = 0; 
    // Return number of existing instances of class Expression
    // Used only for debug purposes
    static std::size_t get_count_expressions();

protected:
    // Default constructor
    explicit Expression() {
        ++count_expressions;
    }

    friend std::ostream& operator<<(std::ostream& os, const Expression& e);

    // Copy constructor
    explicit Expression(const Expression&) {
        ++count_expressions;
    }

    // total number of existing expressions -- only to help to detect bugs in the code
    static std::size_t count_expressions;
};
