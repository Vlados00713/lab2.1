// Lab_03_4.cpp
// < Գ�� ��������� >
// ����������� ������ � 3.4
// ������������, ������ ������� �������.
// ������ 33

#include <iostream>
using namespace std;

int main()
{
    double x; // ������� ��������
    double y; // ������� ��������
    double R; // ������� ��������

    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;
    cout << "R = "; cin >> R;

    // ������������ � ����� ����
    if (((x * x) + (y * y) >= R * R && x >= 0 && y >= 0) ||
        ((x * x) + (y * y) <= R * R && x <= 0 && y <= (x - 1) * (x - 1)))
        cout << "yes" << endl;
    else
        cout << "no" << endl;

    cin.get();
    return 0;
}