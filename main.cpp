#include <iostream>
#include "FuncA.h"
#include "HTTP_Server.h" // Include the header for the HTTP server

int main() {
    // Start the HTTP server
    CreateHTTPserver();

    // Perform the existing calculations
    FuncA calc;
    double x = 1.0; 
    int n = 10;
    std::cout << "FuncA result: " << calc.calculate(x, n) << std::endl;

    return 0;
}