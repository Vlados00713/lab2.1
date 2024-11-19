#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    double x, xp, xk, dx, A, B, y;
    cout << "xp = "; cin >> xp;
    cout << "xk = "; cin >> xk;
    cout << "dx = "; cin >> dx;

    cout << fixed;
    cout << "-------------------------" << endl;
    cout << "|" << setw(5) << "x" << " |"
        << setw(7) << "y" << " |" << endl;
    cout << "-------------------------" << endl;

    x = xp;
    while (x <= xk)
    {
        A = 1 / x + 4;6

        if (x <= 1)
            B = 8 + 0.65 * x;
        else if (x > 5)
            B = sqrt(x + sqrt(2));
        else
            B = log10(x) + (cos((6.1 + x) / 2) / sin((6.1 + x) / 2));

        y = A - B;
        cout << "|" << setw(7) << setprecision(2) << x
            << " |" << setw(10) << setprecision(3) << y << " |" << endl;

        x += dx;
    }
    cout << "-------------------------" << endl;

    return 0;
}
