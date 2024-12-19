#include <iostream>
#include <cassert>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
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

void test_performance() {
    FuncA calc;
    std::vector<double> aValues;
    std::mt19937 mtre{123};
    std::uniform_int_distribution<int> distr{0, 2000000};

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 2000000; i++) {
        aValues.push_back(distr(mtre));
    }

    for (int i = 0; i < 300; i++) {
        for (auto& val : aValues) {
            val = calc.calculate(val, 10); // Using 10 terms for the Taylor series
        }
        std::sort(aValues.begin(), aValues.end());
        std::reverse(aValues.begin(), aValues.end());
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    std::cout << "Performance test time: " << elapsed.count() << " seconds" << std::endl;
    assert(elapsed.count() >= 5.0 && elapsed.count() <= 20.0);
}

int main() {
    test_cos_zero();
    test_cos_pi();
    test_cos_pi_half();
    test_performance();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}