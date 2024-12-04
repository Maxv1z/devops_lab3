#include <iostream>
#include <cassert>
#include "FuncA.h"
#include <cmath>

void test_cos_zero() {
    FuncA calc;
    assert(fabs(calc.calculate(0.0, 5) - 1.0) < 0.001);
}

void test_cos_pi() {
    FuncA calc;
    assert(fabs(calc.calculate(M_PI, 10) + 1.0) < 0.001);
}

void test_cos_pi_half() {
    FuncA calc;
    assert(fabs(calc.calculate(M_PI/2, 10)) < 0.001);
}

int main() {
    test_cos_zero();
    test_cos_pi();
    test_cos_pi_half();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}