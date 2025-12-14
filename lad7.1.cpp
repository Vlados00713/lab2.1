#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

// --- Function to read the graph from an edge list file ---
/**
 * @brief Reads the graph from a file where each line represents an edge (U V).
 * @param filename The path to the input file (e.g., "graph.txt").
 * @param edges Output vector of pairs to store the edges (u, v).
 * @param num_vertices Output reference to store the total number of unique vertices.
 * @return true if the file was read successfully, false otherwise.
 */
bool readEdgeList(const string& filename, vector<pair<int, int>>& edges, int& num_vertices) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file " << filename << endl;
        return false;
    }

    edges.clear();
    set<int> unique_vertices;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        int u, v;
        if (ss >> u >> v) {
            edges.push_back({ u, v });
            unique_vertices.insert(u);
            unique_vertices.insert(v);
        }
    }

    inputFile.close();

    if (unique_vertices.empty()) {
        num_vertices = 0;
        return true;
    }

    // Determine the maximum vertex index to define matrix size
    num_vertices = *unique_vertices.rbegin();

    // Check if the vertex indices start from 1. 
    // If indices are sparse (e.g., 1, 10, 20), this method creates a matrix 
    // of size max(index) x max(index). This is a common approach for simple graph processing.

    return true;
}

// --- Function to build the Adjacency Matrix ---
/**
 * @brief Builds the adjacency matrix from the edge list.
 * @param edges The list of edges (u, v).
 * @param n The number of vertices (size of the matrix).
 * @param matrix Output vector of vectors to store the adjacency matrix.
 */
void buildAdjacencyMatrix(const vector<pair<int, int>>& edges, int n, vector<vector<int>>& matrix) {
    // Initialize matrix of size n x n with zeros.
    // We assume vertices are labeled 1 to n.
    matrix.assign(n, vector<int>(n, 0));

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;

        // Check bounds (assuming 1-based indexing in file, 0-based in matrix)
        if (u >= 1 && u <= n && v >= 1 && v <= n) {
            // Edge from u to v. Set the element at [u-1][v-1]
            matrix[u - 1][v - 1] = 1;
        }
        else {
            cerr << "Warning: Edge (" << u << ", " << v << ") out of expected bounds (1 to " << n << ") and ignored." << endl;
        }
    }
}

// --- Function to calculate vertex degrees ---
/**
 * @brief Calculates the in-degree, out-degree, and total degree for each vertex.
 */
void calculateDegrees(const vector<vector<int>>& matrix, vector<tuple<int, int, int>>& degrees) {
    int n = matrix.size();
    degrees.clear();
    degrees.resize(n); // degrees[i] corresponds to Vertex i+1

    for (int i = 0; i < n; ++i) {
        int out_degree = 0; // Sum of row i
        int in_degree = 0;  // Sum of column i

        // Calculate out-degree (sum of row i)
        for (int j = 0; j < n; ++j) {
            out_degree += matrix[i][j];
        }

        // Calculate in-degree (sum of column i)
        for (int j = 0; j < n; ++j) {
            in_degree += matrix[j][i];
        }

        int total_degree = in_degree + out_degree;

        // Self-loops (A[i][i] = 1) contribute 1 to out-degree and 1 to in-degree, 
        // so they contribute 2 to the total degree (which is standard for simple graphs).

        degrees[i] = make_tuple(in_degree, out_degree, total_degree);
    }
}

// --- Function to check for homogeneity ---
/**
 * @brief Checks if the graph is homogeneous. For a directed graph, this typically
 * means d+(v) = k+ and d-(v) = k- for all vertices v.
 */
bool isHomogeneous(const vector<tuple<int, int, int>>& degrees) {
    if (degrees.empty()) return true;

    // Check consistency for both in-degree and out-degree
    int k_in = get<0>(degrees[0]);
    int k_out = get<1>(degrees[0]);

    for (const auto& deg : degrees) {
        if (get<0>(deg) != k_in || get<1>(deg) != k_out) {
            return false;
        }
    }
    return true;
}

// --- Function to write the results to the file ---
void writeResults(const string& output_filename, const vector<vector<int>>& matrix,
    const vector<tuple<int, int, int>>& degrees, bool is_homogeneous) {

    ofstream outputFile(output_filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not create the output file " << output_filename << endl;
        return;
    }

    // 1. Adjacency Matrix
    outputFile << "Adjacency Matrix:" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            outputFile << val << " ";
        }
        outputFile << endl;
    }

    outputFile << endl;

    // 2. Vertex Degrees
    outputFile << "Vertex degrees:" << endl;
    for (size_t i = 0; i < degrees.size(); ++i) {
        int in_deg = get<0>(degrees[i]);
        int out_deg = get<1>(degrees[i]);
        int total_deg = get<2>(degrees[i]);

        // Output format matching your example result.txt
        outputFile << "Vertex " << (i + 1)
            << ": in = " << in_deg
            << ", out = " << out_deg
            << ", total = " << total_deg << endl;
    }

    outputFile << endl;

    // 3. Homogeneity Check
    if (is_homogeneous) {
        outputFile << "Graph is homogeneous." << endl;
    }
    else {
        outputFile << "Graph is not homogeneous." << endl;
    }

    outputFile.close();
    cout << "Analysis complete. Results written to: " << output_filename << endl;
}

// --- Main execution block ---
int main() {
    string input_filename = "graph.txt";
    string output_filename = "result.txt";

    vector<pair<int, int>> edges;
    int num_vertices = 0;

    // 1. Read the graph from the edge list
    if (!readEdgeList(input_filename, edges, num_vertices)) {
        return 1;
    }

    if (num_vertices == 0) {
        cout << "Graph is empty. Creating empty result file." << endl;
        writeResults(output_filename, {}, {}, true); // Handle empty graph case
        return 0;
    }

    // 2. Build the Adjacency Matrix
    vector<vector<int>> adj_matrix;
    buildAdjacencyMatrix(edges, num_vertices, adj_matrix);

    // 3. Calculate degrees
    vector<tuple<int, int, int>> degrees;
    calculateDegrees(adj_matrix, degrees);

    // 4. Check for homogeneity
    bool is_homogeneous_graph = isHomogeneous(degrees);

    // 5. Write the results to the file
    writeResults(output_filename, adj_matrix, degrees, is_homogeneous_graph);

    return 0;
}