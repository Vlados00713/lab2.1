#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double A(const double x, const double eps, int& n, double& S);
double B(const double x, const int n, double& a);

int main()
{
    double xp, xk, x, dx, eps, a = 0, R = 0, S = 0;
    int n = 0;

    cout << "xp = "; cin >> xp;
    cout << "xk = "; cin >> xk;
    cout << "dx = "; cin >> dx;
    cout << "eps = "; cin >> eps;

    cout << fixed;
    cout << "-------------------------------------------------------------" << endl;
    cout << "|" << setw(5) << "x" << " |"
        << setw(10) << "arctg(x)" << " |"
        << setw(10) << "S" << " |"
        << setw(12) << "n" << " |" << endl;
    cout << "-------------------------------------------------------------" << endl;

    x = xp;
    while (x <= xk)
    {
        A(x, eps, n, S);

        cout << "|" << setw(5) << setprecision(2) << x << " |"
            << setw(10) << setprecision(5) << atan(x) << " |"
            << setw(10) << setprecision(5) << S << " |"
            << setw(12) << n << " |" << endl;

        x += dx;
    }

    cout << "-------------------------------------------------------------" << endl;
    return 0;
}

double A(const double x, const double eps, int& n, double& S)
{
    n = 0;
    double a = x;
    S = a;
    do {
        n++;
        B(x, n, a);
        S += a;
    } while (fabs(a) >= eps);
    return S;
}

double B(const double x, const int n, double& a)
{
    double R = -x * x * (2 * n - 2) / (2 * n + 1);
    a *= R;
    return a;
}
