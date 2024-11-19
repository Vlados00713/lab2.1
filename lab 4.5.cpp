#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
using namespace std;

int main()
{
    double x, y, R;
    srand((unsigned)time(NULL));
    cout << "R = "; cin >> R;
    for (int i = 0; i < 10; i++)
    {
        cout << "x = "; cin >> x;
        cout << "y = "; cin >> y;
        if (((x * x) + (y * y) <= pow(R, 2) && x >= 0 && y <= 0) ||
            ((x * x) + (y * y) <= pow(R, 2) && x >= 0 && y >= (x - 1) * (x - 1)))
            cout << "yes" << endl;
        else
            cout << "no" << endl;
    }

    cout << endl << fixed;
    for (int i = 0; i < 10; i++)
    {
        x = (rand() / (double)RAND_MAX) * (2 * R) - R;
        y = (rand() / (double)RAND_MAX) * (2 * R) - R;
        if (((x * x) + (y * y) <= pow(R, 2) && x >= 0 && y <= 0) ||
            ((x * x) + (y * y) <= pow(R, 2) && x >= 0 && y >= (x - 1) * (x - 1)))

            cout << setw(8) << setprecision(4) << x << " "
            << setw(8) << setprecision(4) << y << " " << "yes" << endl;
        else
            cout << setw(8) << setprecision(4) << x << " "
            << setw(8) << setprecision(4) << y << " " << "no" << endl;
    }

    return 0;
}