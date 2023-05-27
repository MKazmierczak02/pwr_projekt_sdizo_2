#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <fstream>

const int INF = std::numeric_limits<int>::max(); // Wartość reprezentująca brak krawędzi
using namespace std;

struct Edge {
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class GraphMatrix {
private:
    int size;
    int **adjacencyMatrix;
    int numVertices;
    bool directed;
public:
    // Konstruktor
    GraphMatrix(int n, bool directed) : numVertices(n) {
        this->size = n;
        fillUpMatrix();
        this->directed=directed;
    }

    // Dodaj krawędź o określonej wadze między wierzchołkami u i v
    void addEdge(int u, int v, int weight) {
        if (u>numVertices || v>=numVertices || weight < 0){
            cout << "index out of bounds" << endl;
            return;
        }
        // zaleznie czy graf jest skierowany
        adjacencyMatrix[u][v] = weight;
        if (!directed){
            adjacencyMatrix[v][u] = weight;
        }
    }

    // Usuń cały graf
    ~GraphMatrix() {
        adjacencyMatrix = nullptr;
        delete adjacencyMatrix;
        size = 0;
        numVertices = 0;
    }

    void fillUpMatrix(){
        int** matrix = new int*[size];
        for (int i = 0; i < size; i++) {
            matrix[i] = new int[size];
        }
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                matrix[i][j]=INF;
            }
        }
        adjacencyMatrix = matrix;
    }

    // Wyświetl macierz wag
    void displayMatrix() {
        for (int i = 0; i < numVertices; ++i) {cout << setw(5) << i;}
        cout << endl;
        for (int i = 0; i < numVertices; ++i) {
            cout << i << " ";
            for (int j = 0; j < numVertices; ++j) {
                if (adjacencyMatrix[i][j] == INF)
                    std::cout << std::setw(5) << "INF";
                else
                    std::cout << std::setw(3) << adjacencyMatrix[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }
    int getNumVertices(){
        return numVertices;
    }

    int getWeight(int i, int j){
        return adjacencyMatrix[i][j];
    }

    static bool compareEdges(const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    }

    bool isDirected(){
        return directed;
    }

    int findParent(std::vector<int>& parent, int v) {
        // Znajdowanie korzenia zbioru rozłącznego zawierającego wierzchołek
        if (parent[v] != v) {
            parent[v] = findParent(parent, parent[v]);
        }
        return parent[v];
    }

    void unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
        // Łączenie dwóch zbiorów rozłącznych na podstawie rangi
        int parentX = findParent(parent, x);
        int parentY = findParent(parent, y);

        if (rank[parentX] < rank[parentY]) {
            parent[parentX] = parentY;
        } else if (rank[parentX] > rank[parentY]) {
            parent[parentY] = parentX;
        } else {
            parent[parentY] = parentX;
            rank[parentX]++;
        }
    }

    GraphMatrix minimumSpanningTreeKruskal(GraphMatrix graph) {
        int numVertices = graph.getNumVertices();
        std::vector<Edge> edges;

        // Tworzenie listy krawędzi na podstawie macierzy sąsiedztwa
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                int weight = graph.getWeight(i, j);
                if (weight != INF) {
                    edges.push_back(Edge(i, j, weight));
                }
            }
        }

        // Sortowanie krawędzi w kolejności rosnącej wag
        std::sort(edges.begin(), edges.end(), compareEdges);

        // Tworzenie nowej instancji grafu MST
        GraphMatrix mstGraph(numVertices, graph.isDirected());

        // Inicjalizacja zbiorów rozłącznych dla każdego wierzchołka
        std::vector<int> parent(numVertices);
        std::vector<int> rank(numVertices, 0);

        for (int i = 0; i < numVertices; ++i) {
            parent[i] = i;
        }

        // Przechodzenie po posortowanych krawędziach i dodawanie ich do MST
        int addedEdges = 0;
        for (const Edge& edge : edges) {
            int u = edge.u;
            int v = edge.v;

            // Sprawdzenie, czy krawędź łączy dwa różne zbiory rozłączne
            int parentU = findParent(parent, u);
            int parentV = findParent(parent, v);
            if (parentU != parentV) {
                mstGraph.addEdge(u, v, edge.weight);
                unionSets(parent, rank, parentU, parentV);
                ++addedEdges;
            }

            // Jeśli MST zawiera już wszystkie wierzchołki, przerwij algorytm
            if (addedEdges == numVertices - 1) {
                break;
            }
        }

        return mstGraph;
    }

    GraphMatrix minimumSpanningTreePrim(GraphMatrix graph) {
        int numVertices = graph.getNumVertices();
        int startVertex = 0;
        // Tworzenie nowej instancji grafu MST
        GraphMatrix mstGraph(numVertices, graph.isDirected());

        std::vector<int> key(numVertices, std::numeric_limits<int>::max()); // Tablica kluczy (wagi)
        std::vector<int> parent(numVertices, -1); // Tablica poprzedników w MST
        std::vector<bool> inMST(numVertices, false); // Tablica oznaczająca, czy wierzchołek należy już do MST

        // Ustawienie klucza startowego na 0
        key[startVertex] = 0;

        // Kolejka priorytetowa posortowana wg key
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
        pq.push(std::make_pair(0, startVertex));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            // Przeszukiwanie sąsiadujących wierzchołków
            for (int v = 0; v < numVertices; ++v) {
                int weight = graph.getWeight(u, v);

                if (weight != std::numeric_limits<int>::max() && !inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push(std::make_pair(key[v], v));
                }
            }
        }

        // Dodawanie krawędzi do MST w oparciu o tablicę poprzedników
        for (int v = 0; v < numVertices; ++v) {
            if (parent[v] != -1) {
                mstGraph.addEdge(v, parent[v], graph.getWeight(v, parent[v]));
            }
        }

        return mstGraph;
    }

    static GraphMatrix graphMatrixloadFromFile(const string& fileName) {
        fstream file(fileName);
        int size;
        int u, v, weight;
        if(file.is_open())
        {
            file >> size;
            GraphMatrix graph = GraphMatrix(size, false);
            if(file.fail())
                cout << "File error - READ SIZE" << endl;
            else
                while (!file.eof())
                {
                    file >> u;
                    file >> v;
                    file >> weight;
                    if(file.fail())
                    {
                        cout << "File error - READ DATA" << endl;
                        break;
                    }
                    else
                        graph.addEdge(u, v, weight);
                }
            file.close();
            return graph;
        }
        else {
            cout << "File error - OPEN" << endl;
            GraphMatrix graph = GraphMatrix(size, false);
            return graph;
        }
    }
};