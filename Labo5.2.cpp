#include <iostream>
#include <iomanip>
#include <cmath>

// Function to calculate the next term of the Taylor series
double nextTerm(double prevTerm, double x, int n) {
    return -prevTerm * x * x / n; // Recursive relation for the series
}

// Function to compute the Taylor series sum
double taylorSeriesSum(double x, double eps, int& termsCount) {
    double term = 1.0;   // The first term of the series for e^(-x^2)
    double sum = term;   // Initial sum
    termsCount = 1;      // Term counter

    while (std::abs(term) > eps) {
        term = nextTerm(term, x, termsCount);
        sum += term;
        termsCount++;
    }
    return sum;
}

// Main program
int main() {
    double xStart, xEnd, dx, eps;

    // Input parameters
    std::cout << "Enter the start of the interval (xStart): ";
    std::cin >> xStart;
    std::cout << "Enter the end of the interval (xEnd): ";
    std::cin >> xEnd;
    std::cout << "Enter the step size (dx): ";
    std::cin >> dx;
    std::cout << "Enter the precision (eps): ";
    std::cin >> eps;

    // Print table header
    std::cout << std::setw(10) << "x"
        << std::setw(20) << "e^(-x^2) (std)"
        << std::setw(20) << "Taylor Sum"
        << std::setw(20) << "Terms Count" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    // Calculate values over the interval
    for (double x = xStart; x <= xEnd; x += dx) {
        int termsCount = 0; // Term counter
        double taylorSum = taylorSeriesSum(x * x, eps, termsCount); // Taylor series sum
        double exactValue = std::exp(-x * x); // Exact value of e^(-x^2)

        // Print table row
        std::cout << std::setw(10) << x
            << std::setw(20) << exactValue
            << std::setw(20) << taylorSum
            << std::setw(20) << termsCount << std::endl;
    }

    return 0;
}
