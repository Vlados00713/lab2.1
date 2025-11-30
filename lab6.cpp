#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>

// --- Структура для зберігання графу ---
struct DirectedGraph {
    int num_vertices = 0;
    int num_edges = 0;
    // Список суміжності: зберігає вершини (0-based)
    std::vector<std::vector<int>> adj_list;
    // Список ребер: зберігає пари (v, u) (1-based, як у файлі)
    std::vector<std::pair<int, int>> edge_list;
};

// --- Оголошення функцій (прототипи) ---
void outputMatrix(const std::vector<std::vector<int>>& matrix, const std::string& title,
    const std::string& output_filename, int num_rows, int num_cols);
DirectedGraph readGraphFromFile(const std::string& filename);
void printAdjacencyMatrix(const DirectedGraph& graph, const std::string& output_filename);
void printIncidenceMatrix(const DirectedGraph& graph, const std::string& output_filename);


// --- Реалізація функції: Виведення матриці ---
void outputMatrix(const std::vector<std::vector<int>>& matrix, const std::string& title,
    const std::string& output_filename, int num_rows, int num_cols) {

    // Відкриваємо файл у режимі додавання (app)
    std::ofstream outfile(output_filename, std::ios_base::app);

    // --- Вивід у Консоль ---
    std::cout << "\n--- " << title << " ---" << std::endl;
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            std::cout << matrix[i][j] << (j == num_cols - 1 ? "" : "\t");
        }
        std::cout << std::endl;
    }

    // --- Вивід у Файл ---
    if (outfile.is_open()) {
        outfile << "\n--- " << title << " ---\n";

        // Виведення заголовків для Матриці Інцідентності
        if (title.find("Incidence Matrix") != std::string::npos) {
            outfile << "V\\E ";
            for (int j = 1; j <= num_cols; ++j) {
                outfile << j << (j == num_cols ? "" : " ");
            }
            outfile << "\n";
        }

        for (int i = 0; i < num_rows; ++i) {
            // Виведення індексу вершини для Матриці Інцідентності
            if (title.find("Incidence Matrix") != std::string::npos) {
                outfile << i + 1 << "   ";
            }

            for (int j = 0; j < num_cols; ++j) {
                outfile << matrix[i][j] << (j == num_cols - 1 ? "" : " ");
            }
            outfile << "\n";
        }
        outfile.close();
        std::cout << title << " successfully written to " << output_filename << std::endl;
    }
}

// --- Реалізація функції: Зчитування графу ---
DirectedGraph readGraphFromFile(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error: Could not open input file " << filename << std::endl;
        return DirectedGraph();
    }

    DirectedGraph graph;
    int n, m;

    // 1. Зчитування n (вершин) та m (ребер)
    if (!(infile >> n >> m) || n <= 0 || m <= 0) {
        std::cerr << "Error: Invalid n or m in the file header." << std::endl;
        return DirectedGraph();
    }

    graph.num_vertices = n;
    graph.num_edges = m;
    graph.adj_list.resize(n);

    int v, u;
    // ВИПРАВЛЕНО C4267: Використовуємо size_t для 'i' для усунення попередження
    for (size_t i = 0; i < (size_t)m; ++i) {

        // 2. Зчитування ребра (v, u)
        if (!(infile >> v >> u)) {
            std::cerr << "Error: Could not read edge " << i + 1 << ". Stopping." << std::endl;
            break;
        }

        // Перевірка індексів (якщо вони невалідні, ігноруємо ребро)
        // ВИПРАВЛЕНО E0018: Гарантовано коректний синтаксис умови if
        if (v < 1 || v > n || u < 1 || u > n)
        {
            // Зменшуємо лічильник m, оскільки ребро не додається
            graph.num_edges--;
            continue;
        }

        // 3. Додавання до Списку Суміжності (використовуючи 0-based indexing)
        int start_vertex_0based = v - 1;
        int end_vertex_0based = u - 1;
        graph.adj_list[start_vertex_0based].push_back(end_vertex_0based);

        // 4. Додавання до Списку Ребер (для Матриці Інцідентності)
        graph.edge_list.push_back({ v, u });
    }

    // Коригуємо кількість ребер на фактичну
    graph.num_edges = graph.edge_list.size();

    std::cout << "Successfully read graph with " << graph.num_vertices
        << " vertices and " << graph.num_edges << " valid edges." << std::endl;

    return graph;
}

// --- Реалізація функції: Матриця Суміжності ---
void printAdjacencyMatrix(const DirectedGraph& graph, const std::string& output_filename) {
    int n = graph.num_vertices;

    if (n == 0) return;

    std::vector<std::vector<int>> adj_matrix(n, std::vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int neighbor_0based : graph.adj_list[i]) {
            adj_matrix[i][neighbor_0based] = 1;
        }
    }

    outputMatrix(adj_matrix, "Adjacency Matrix (Rows/Cols are 1-based Vertices)",
        output_filename, n, n);
}

// --- Реалізація функції: Матриця Інцідентності ---
void printIncidenceMatrix(const DirectedGraph& graph, const std::string& output_filename) {
    int n = graph.num_vertices; // Рядки (Вершини)
    int m = graph.num_edges;    // Стовпці (Ребра)

    if (n == 0 || m == 0) return;

    std::vector<std::vector<int>> inc_matrix(n, std::vector<int>(m, 0));

    // Індекс 'j' — це 0-базовий індекс ребра (стовпець)
    for (int j = 0; j < m; ++j) {
        int v_1based = graph.edge_list[j].first;  // Хвіст (+1)
        int u_1based = graph.edge_list[j].second; // Голова (-1)

        int v_0based = v_1based - 1;
        int u_0based = u_1based - 1;

        // +1 у рядку хвоста
        inc_matrix[v_0based][j] = 1;

        // -1 у рядку голови
        inc_matrix[u_0based][j] = -1;
    }

    outputMatrix(inc_matrix, "Incidence Matrix (Rows=Vertices 1-n, Cols=Edges 1-m, +1=Tail, -1=Head)",
        output_filename, n, m);
}


// --- Головна функція (main) ---
int main() {
    // Вхідний та вихідний файли
    const std::string input_file = "graph_input.txt";
    const std::string output_file = "graph_output.txt";

    // --- 1. Setup: Створення вхідного файлу для тестування ---
    std::cout << "--- Setup: Creating Input File ---\n";
    std::ofstream dummy_input(input_file);
    if (dummy_input.is_open()) {
        dummy_input << "4 5\n";
        dummy_input << "1 2\n";
        dummy_input << "2 3\n";
        dummy_input << "3 4\n";
        dummy_input << "4 1\n";
        dummy_input << "2 4\n";
        dummy_input.close();
        std::cout << "Created dummy input file: " << input_file << std::endl;
    }
    else {
        std::cerr << "FATAL ERROR: Could not create dummy input file. Exiting." << std::endl;
        return 1;
    }

    // --- 2. Setup: Ініціалізація/Очищення вихідного файлу ---
    std::cout << "\n--- Setup: Initializing Output File ---\n";
    std::ofstream clear_output(output_file, std::ios_base::trunc);
    if (clear_output.is_open()) {
        clear_output << "Graph Analysis Results\n\n";
        clear_output.close();
        std::cout << "Cleared/initialized output file: " << output_file << std::endl;
    }
    else {
        std::cerr << "FATAL ERROR: Could not initialize output file. Exiting." << std::endl;
        return 1;
    }

    // 3. Task 1: Зчитування графу
    std::cout << "\n--- Task 1: Reading Graph ---\n";
    DirectedGraph my_graph = readGraphFromFile(input_file);

    if (my_graph.num_vertices == 0 || my_graph.num_edges == 0) {
        std::cerr << "\nGraph loading failed or graph is empty. Exiting." << std::endl;
        return 1;
    }

    // 4. Task 2: Виведення матриць
    std::cout << "\n--- Task 2: Generating Matrices ---\n";
    char choice;
    std::cout << "Do you want to output the Adjacency and Incidence matrices? (Y/N): ";

    if (!(std::cin >> choice) || std::toupper(choice) != 'Y') {
        std::cout << "Matrix output skipped by user request." << std::endl;
    }
    else {
        printAdjacencyMatrix(my_graph, output_file);
        printIncidenceMatrix(my_graph, output_file);
    }

    std::cout << "\nProgram finished. Check console output and " << output_file << std::endl;
    return 0;
}