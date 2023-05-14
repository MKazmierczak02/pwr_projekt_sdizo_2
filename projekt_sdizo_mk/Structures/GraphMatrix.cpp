#include <iostream>
#include <vector>
#include <limits>
using namespace std;
const int INF = std::numeric_limits<int>::max(); // Wartość reprezentująca brak krawędzi

class GraphMatrix {
private:
    std::vector<std::vector<int>> adjacencyMatrix;
    int numVertices;

public:
    // Konstruktor
    GraphMatrix(int n) : numVertices(n) {
        adjacencyMatrix.resize(n, std::vector<int>(n, INF));
    }

    // Dodaj krawędź o określonej wadze między wierzchołkami u i v
    void addEdge(int u, int v, int weight) {
        if (u>numVertices || v>=numVertices || weight < 0){
            cout << "index out of bounds" << endl;
            return;
        }
        adjacencyMatrix[u][v] = weight;
        adjacencyMatrix[v][u] = weight; // zaleznie czy graf jest skierowany
    }

    // Usuń cały graf
    void removeGraph() {
        adjacencyMatrix.clear();
        numVertices = 0;
    }

    // Wyświetl macierz wag
    void displayMatrix() {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] == INF)
                    std::cout << "INF ";
                else
                    std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};