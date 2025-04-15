/*******************************
 * Lab 3: exercise 2            *
 * Test polynomial class        *
 *******************************/

#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include "polynomial.h"

int main() {
    /*********************************************
     * Test 1: constructors,                     *
     *         conversion to string, and         *
     *         degree()                          *
     *********************************************/
    std::cout << "** Test 1: constructors, conversion to string, and degree()\n\n";

    // Create Polynomial p0 = 0
    Polynomial p0;
    assert(std::string(p0) == std::string("0"));
    assert(p0.degree() == 0);

    // Create Polynomial p1 = 5
    Polynomial p1{5};
    assert(std::string(p1) == std::string("5X^0"));
    assert(p1.degree() == 0);

    // Create Polynomial p2 = 2X^2
    Polynomial p2{2, 2};
    assert(std::string(p2) == std::string("2X^2"));
    assert(p2.degree() == 2);

    // Create polynomial p1 = 2X^1 - 5X^2 + X^6
    Polynomial p3{{{1, 2}, {2, -5}, {6, 1}}};
    assert(std::string(p3) == std::string("2X^1 - 5X^2 + 1X^6"));
    assert(p3.degree() == 6);

    // Create polynomial p2 = -8X^0 + 2X^1 + 5X^2 + 10X^4 - X^6 + 3X^16
    Polynomial p4{{{0, -8}, {1, 2}, {2, 5}, {4, 10}, {6, -1}, {16, 3}}};
    assert(std::string(p4) == std::string("-8X^0 + 2X^1 + 5X^2 + 10X^4 - 1X^6 + 3X^16"));
    assert(p4.degree() == 16);

    /*********************************************
     * Test 2: operator+=                        *
     **********************************************/
    std::cout << "** Test 2: operator+=\n\n";

    p3 += p4;
    assert(std::string(p3) == std::string("-8X^0 + 4X^1 + 10X^4 + 3X^16"));
    assert(p3.degree() == 16);

    /*********************************************
     * Test 3: operator-=                        *
     **********************************************/
    std::cout << "** Test 3:  operator-=\n\n";

    p3 -= p4;
    assert(std::string(p3) == std::string("2X^1 - 5X^2 + 1X^6"));
    assert(p3.degree() == 6);

    /*********************************************
     * Test 4: operator*= and                     *
     **********************************************/
    std::cout << "** Test 4:  operator*=\n\n";

    p3 *= p4;
    assert(std::string(p3) == std::string("-16X^1 + 44X^2 - 25X^4 + 20X^5 - 58X^6 + 10X^8 + 10X^10 "
                                          "- 1X^12 + 6X^17 - 15X^18 + 3X^22"));
    assert(p3.degree() == 22);

    /*********************************************
     * Test 5: operator==                         *
     **********************************************/
    assert(p3 == Polynomial({{1, -16},
                             {2, 44},
                             {4, -25},
                             {5, 20},
                             {6, -58},
                             {8, 10},
                             {10, 10},
                             {12, -1},
                             {17, 6},
                             {18, -15},
                             {22, 3}}));

    /*************************************************
     * Test 6: operator+, operator-, operator*, and  *
     *         operator<<                            *
     *************************************************/
    std::cout << "** Test 6:  operator+, operator-, operator*, operator<<\n\n";

    p4 = p3 * p3;
    std::cout << "p4 = " << p4 << "\n\n";
    assert(p4.degree() == 44);

    p0 = Polynomial({{11, -2640},
                     {12, 3744},
                     {13, 432},
                     {14, -1748},
                     {15, 400},
                     {16, -1010},
                     {17, -40},
                     {18, 124},
                     {19, 1008},
                     {20, -1240},
                     {21, -300},
                     {22, 970},
                     {23, -1392},
                     {24, 2005},
                     {25, 120},
                     {26, -450},
                     {27, 240}});

    p0 = p4 - p0 + p1 * p2;
    assert(std::string(p0) ==
           std::string("266X^2 - 1408X^3 + 1936X^4 + 800X^5 - 2840X^6 + 3616X^7 - 4479X^8 - "
                       "1320X^9 + 4180X^10 - 648X^28 - 12X^29 + 90X^30 + 60X^32 + 30X^34 - 180X^35 "
                       "+ 225X^36 + 36X^39 - 90X^40 + 9X^44"));
    assert(p0.degree() == 44);

    /*************************************************
     * Test 7: mixed-mode operations                 *
     *************************************************/
    std::cout << "** Test 7: mixed-mode operations\n\n";

    Polynomial p5{2 * p0 - p0 + 100};
    p5 -= 1;

    assert(std::string(p5) ==
           std::string("99X^0 + 266X^2 - 1408X^3 + 1936X^4 + 800X^5 - 2840X^6 + 3616X^7 - 4479X^8 "
                       "- 1320X^9 + 4180X^10 - 648X^28 - 12X^29 + 90X^30 + 60X^32 + 30X^34 - "
                       "180X^35 + 225X^36 + 36X^39 - 90X^40 + 9X^44"));
    assert(p5.degree() == 44);

    p0 = 5;
    assert(p0 == p1);
    assert(5 == p0);
    assert(p0 != p3);

    std::cout << "Success\n";

}
