#include "FuncA.h"
#include <cmath>

double FuncA::calculate(double x, int n) {
// Calculate cosine using Taylor series
    // cos(x) = 1 - (x²/2!) + (x⁴/4!) - ... + ((-1)ⁿ * x²ⁿ)/(2n)!
    double result = 1.0;
    double term = 1.0;
    
    for (int i = 1; i <= n; i++) {
        term *= -1.0 * x * x / (2 * i * (2 * i - 1));
        result += term;
    }
    
    return result;
}
