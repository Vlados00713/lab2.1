// Lab_03_2.cpp
// <Філь Владислав>
// Лабораторна робота № 3.2
// Розгалуження, задане формулою: функція з параметрами.
// Варіант 33

#include <iostream>
using namespace std;

int main()
{
    double x; // вхідний аргумент
    double a; // вхідний параметр
    double b; // вхідний параметр
    double c; // вхідний параметр
    double F; // результат обчислення виразу

    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "x = "; cin >> x;

    // спосіб 1: розгалуження в скороченій формі
    if (a < 0 && x != 0)
        F = a * (x * x) + (b * b) * x;
    if (a > 0 && x == 0)
        F = x - (a / (x - c));
    if (!(a < 0 && x != 0) && !(a > 0 && x == 0))
        F = 1 + (x / c);

    cout << endl;
    cout << "1) F = " << F << endl;

    // спосіб 2: розгалуження в повній формі
    if (a < 0 && x != 0)
        F = a * (x * x) + (b * b) * x;
    else
        if (a > 0 && x == 0)
            F = x - (a / (x - c));
        else
            F = 1 + (x / c);

    cout << "2) F = " << F << endl;

    cin.get();
    return 0;
}