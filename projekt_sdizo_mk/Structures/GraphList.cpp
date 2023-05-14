#include <iostream>
#include <list>

class GraphList {
private:
    int numVertices;
    std::list<std::pair<int, int>>* adjacencyList;

public:
    // Konstruktor
    GraphList(int n) : numVertices(n) {
        adjacencyList = new std::list<std::pair<int, int>>[n];
    }

    // Dodaj krawędź o określonej wadze między wierzchołkami u i v
    void addEdge(int u, int v, int weight) {
        adjacencyList[u].push_back(std::make_pair(v, weight));
        adjacencyList[v].push_back(std::make_pair(u, weight)); // zaleznie czy graf jest skierowany
    }

    // Usuń cały graf
    void removeGraph() {
        delete[] adjacencyList;
        adjacencyList = nullptr;
        numVertices = 0;
    }

    // Wyświetl listę sąsiadów dla każdego wierzchołka
    void displayList() {
        for (int i = 0; i < numVertices; ++i) {
            std::cout << "Sąsiedzi wierzchołka " << i << ": ";
            for (const auto& neighbor : adjacencyList[i]) {
                std::cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            std::cout << std::endl;
        }
    }
};
