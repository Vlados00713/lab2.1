#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Функція для звільнення матриці
void deleteAdjMatrix(int**& adj, int n) {
    if (adj != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] adj[i];
        }
        delete[] adj;
        adj = nullptr; // Встановлюємо в nullptr, щоб запобігти подвійному звільненню
    }
}

// Функція для зчитування графа з файлу та створення матриці
// ПОПЕРЕДЖЕННЯ: Використовує динамічну пам'ять (int**), яку потрібно звільняти вручну!
int** readGraphAndCreateMatrix(const string& filename, int& n, int& m) {
    ifstream fin(filename);
    if (!fin.is_open()) {
        cerr << "Error: cannot open file " << filename << "!\n";
        n = 0;
        m = 0;
        return nullptr;
    }

    // 1. Зчитуємо розміри
    if (!(fin >> n >> m)) {
        cerr << "Error: Invalid graph dimensions in file " << filename << ".\n";
        n = 0; m = 0;
        return nullptr;
    }

    // 2. ДИНАМІЧНЕ ВИДІЛЕННЯ МАТРИЦІ КОРЕКТНОГО РОЗМІРУ N x N
    int** adj = new int* [n];
    for (int i = 0; i < n; i++) {
        // Ініціалізуємо нулями
        adj[i] = new int[n] {};
    }

    // 3. Зчитуємо ребра
    for (int i = 0; i < m; i++) {
        int u, v;
        if (!(fin >> u >> v)) break;

        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            adj[u - 1][v - 1] = 1;
        }
    }

    fin.close();
    return adj;
}

// Функція для обчислення вхідних та вихідних степенів
void calculateDegrees(int** adj, int n, int* inDeg, int* outDeg) {
    for (int i = 0; i < n; i++) {
        inDeg[i] = 0;
        outDeg[i] = 0;
        for (int j = 0; j < n; j++) {
            outDeg[i] += adj[i][j];
            inDeg[i] += adj[j][i];
        }
    }
}

// Функція для виводу висячих та ізольованих вершин (як у вашому прикладі)
void printHangingAndIsolated(int* inDeg, int* outDeg, int n) {
    bool hasHanging = false;
    bool hasIsolated = false;

    cout << "Hanging vertices: ";
    for (int i = 0; i < n; i++) {
        int total = inDeg[i] + outDeg[i];
        if (total == 1) {
            cout << (i + 1) << " ";
            hasHanging = true;
        }
    }
    if (!hasHanging) cout << "None";
    cout << endl;

    cout << "Isolated vertices: ";
    for (int i = 0; i < n; i++) {
        int total = inDeg[i] + outDeg[i];
        if (total == 0) {
            cout << (i + 1) << " ";
            hasIsolated = true;
        }
    }
    if (!hasIsolated) cout << "None";
    cout << endl;
}

int main() {
    string inputFile;
    cout << "Enter input file name: ";
    cin >> inputFile;

    int n = 0; // Кількість вершин
    int m = 0; // Кількість ребер

    // 1. Зчитування графа та створення матриці коректного розміру
    // (Повертає nullptr у разі помилки)
    int** adj = readGraphAndCreateMatrix(inputFile, n, m);

    if (adj == nullptr || n == 0) {
        // Вихід, якщо файл не знайдено або порожній
        if (adj != nullptr) deleteAdjMatrix(adj, n); // Звільняємо, якщо повернуто, але n=0
        return 1;
    }

    // 2. ДИНАМІЧНЕ ВИДІЛЕННЯ МАСИВІВ СТЕПЕНІВ КОРЕКТНОГО РОЗМІРУ N
    int* inDeg = new int[n] {};
    int* outDeg = new int[n] {};

    // 3. Обчислення степенів
    calculateDegrees(adj, n, inDeg, outDeg);

    // 4. Вивід висячих та ізольованих вершин (на консоль)
    printHangingAndIsolated(inDeg, outDeg, n);

    // 5. ВІДНОВЛЕННЯ ЧАСТИНИ ЛОГІКИ ЗВІЛЬНЕННЯ ПАМ'ЯТІ (Критично важливо!)
    deleteAdjMatrix(adj, n);
    delete[] inDeg;
    delete[] outDeg;

    return 0;
}