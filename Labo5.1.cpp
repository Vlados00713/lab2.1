#include <iostream>
#include <cmath> // For sin and sqrt functions

// Function f(x)
double f(double x) {
    double numerator = 1 + x * x + x * x * x * x; // 1 + x^2 + x^4
    double denominator = 1 + x * x;              // 1 + x^2
    return sin(numerator / denominator);         // sin(numerator / denominator)
}

int main() {
    // Input value of s
    double s;
    std::cout << " s: ";
    std::cin >> s;

    // Calculate f(s)
    double fs = f(s);

    // Calculate f^2(1 + s)
    double f_squared_1_plus_s = pow(f(1 + s), 2);

    // Calculate the square root term
    double sqrt_term = sqrt(1 + f_squared_1_plus_s * (1 + s * s));

    // Final result
    double result = (5 * fs + 3 * f_squared_1_plus_s + 1) / (1 + sqrt_term);

    // Output the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
