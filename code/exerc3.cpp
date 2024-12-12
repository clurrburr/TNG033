/*********************************************
 * Lab 3: exercise 3                         *
 * Program to compute an approximation of pi *
 * STL-algorithms should be used             *
 *********************************************/

#include <iostream>
#include <vector>
#include <format>
#include <numeric>
#include <algorithm>
#include <cmath>

double calc(double termsN);

int main() {
    std::cout << "Enter number of terms: ";
    int n;
    std::cin >> n;

    // ADD CODE
    std::vector<double> terms(n); //vector with n slots
    std::iota(terms.begin(), terms.end(), 0); //initialize the slots with 0 to n

    std::vector<double> power{ terms }; // copy the vector

    //transforms the vector terms to the first parathesis
    std::transform(terms.begin(), terms.end(), terms.begin(), [](double& termsN) {return calc(termsN);});
    //transforms the vector power to the second parathesis
    std::transform(power.begin(), power.end(), power.begin(), [](double& powerN) {return std::pow(16.0, powerN * (-1));});
    //dot product between the vectors terms and power
    double result = std::inner_product(std::begin(terms), std::end(terms), std::begin(power), 0.0);

    std::cout << std::format("{:.10f}\n", result);
}

double calc(double termsN) {
    const double factor = 8.0 * termsN;
    const double formula = 4.0 / (factor + 1.0) - 2.0 / (factor + 4.0) - 1 / (factor + 5.0) - 1 / (factor + 6.0);

    return formula;
}