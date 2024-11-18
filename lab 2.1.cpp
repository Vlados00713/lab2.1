#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double alpha, beta;
    cout << "Enter z  ";
    cin >> alpha >> beta;

    double z1 = (sin(alpha) + cos(2 * beta - alpha)) / (cos(alpha) - sin(2 * beta - alpha));
    double z2 = (1 + sin(2 * beta)) / cos(2 * beta);

    cout << "Z1 = " << z1 << "\nZ2 = " << z2 << endl;
    return 0;
}
