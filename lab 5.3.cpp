#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double z(const double x);

int main()
{
    double pp, pk, c;
    int n;

    cout << "pp = "; cin >> pp;
    cout << "pk = "; cin >> pk;
    cout << "n = "; cin >> n;

    cout << fixed;
    cout << "-------------------------" << endl;
    cout << "|" << setw(7) << "p" << " |"
        << setw(7) << "result" << " |" << endl;
    cout << "-------------------------" << endl;

    double pg = (pk - pp) / n;
    double p = pp;
    while (p <= pk)
    {
        c = z(pow(p, 2) + 1) - z(pow(p, 2) - 1) + 2 * z(p);

        cout << "|" << setw(7) << setprecision(2) << p << " |"
            << setw(7) << c << " |" << endl;

        p += pg;
    }

    cout << "-------------------------" << endl;
    return 0;
}

double z(const double x)
{
    if (abs(x) >= 1)
        return (sin(x) + 1) / (pow(cos(x), 2) + exp(x));
    else
    {
        double S = 0;
        int k = 0;
        double a = 1;
        S = a;
        do {
            k++;
            double R = 2 * x / k;
            a *= R;
            S += a;
        } while (k < 6);

        S += 1 / exp(pow(x, 2));
        return S;
    }
}
