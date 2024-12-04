#include <iostream>
#include "FuncA.h"

int main() {
    FuncA calc;
    double x = 1.0;
    int n = 10; 
    std::cout << "FuncA result: " << calc.calculate(x, n) << std::endl;
    return 0;
}
