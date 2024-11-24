#include <iostream>
#include <cmath>

using namespace std;

double p(const double x);

int main()
{
    double s;
    cout << "s = "; cin >> s;
    double R = (pow(p(1 + pow(s, 2)), 2) + pow(p(1 - pow(s, 3)), 3)) / 1 + p(10 * s);
    cout << "R = " << R << endl;
    return 0;
}

double p(const double x)
{
    return 1 + pow(sin(x), 2);
}
