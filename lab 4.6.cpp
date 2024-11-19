#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double P, S;
    int k, i;
    P = 1;
    k = 1;

    // Перша реалізація циклу з while
    while (k <= 15) {
        S = 0;
        i = 1;
        while (i <= k) {
            S += i + 1;
            i++;
        }
        P *= sqrt(1 + pow(S, 2)) / (1 + S);
        k++;
    }
    cout << P << endl;

    // Друга реалізація циклу з do-while
    P = 1;
    k = 1;
    do {
        S = 0;
        i = 1;
        do {
            S += i + 1;
            i++;
        } while (i <= k);
        P *= sqrt(1 + pow(S, 2)) / (1 + S);
        k++;
    } while (k <= 15);
    cout << P << endl;

    // Третя реалізація циклу з for (зростання)
    P = 1;
    for (k = 1; k <= 15; k++) {
        S = 0;
        for (i = 1; i <= k; i++) {
            S += i + 1;
        }
        P *= sqrt(1 + pow(S, 2)) / (1 + S);
    }
    cout << P << endl;

    // Четверта реалізація циклу з for (спадання)
    P = 1;
    for (k = 15; k >= 1; k--) {
        S = 0;
        for (i = k; i >= 1; i--) {
            S += i + 1;
        }
        P *= sqrt(1 + pow(S, 2)) / (1 + S);
    }
    cout << P << endl;

    return 0;
}