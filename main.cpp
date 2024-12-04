#include <iostream>
#include "FuncA.h"

int main() {
    FuncA calc;
    double x = 1.0; // Example value for x
    int n = 10; // Example value for n
    std::cout << "FuncA result: " << calc.calculate(x, n) << std::endl;
    return 0;
}
