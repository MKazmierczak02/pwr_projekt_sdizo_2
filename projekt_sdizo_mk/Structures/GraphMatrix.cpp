#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <fstream>

using namespace std;
class Edge {
public:
    int u, v, weight;

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    static bool compareEdges(const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    }
};
const int INF = numeric_limits<int>::max(); // Wartość reprezentująca brak krawędzi


class GraphMatrix {

private:
    int  num_vertices;
    int **adjacencyMatrix;
    int vf, vl;
public:

    // Konstruktor
    GraphMatrix(int n, int vf, int vl) {
        this-> num_vertices = n; // ilosc wierzcholkow
        this->vf = vf; // wierzcholek poczatkowy dla najkrotszej drogi
        this->vl = vl; // wierzcholek koncowy dla najkrotszej drogi
        fillUpMatrix();
    }

    // Dodaj krawędź o określonej wadze między wierzchołkami u i v
    void addEdge(int u, int v, int weight, bool directed) {
        if (u>num_vertices || v>=num_vertices || weight < 0){
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
         num_vertices = 0;
        num_vertices = 0;
    }

    void fillUpMatrix(){
        int** matrix = new int*[ num_vertices];
        for (int i = 0; i <  num_vertices; i++) {
            matrix[i] = new int[ num_vertices];
        }
        for(int i=0; i< num_vertices; i++){
            for(int j=0; j< num_vertices; j++){
                matrix[i][j]=INF;
            }
        }
        adjacencyMatrix = matrix;
    }

    // Wyświetl macierz wag
    void displayMatrix() {
        for (int i = 0; i < num_vertices; ++i) {cout << setw(5) << i;}
        cout << endl;
        for (int i = 0; i < num_vertices; ++i) {
            cout << i << " ";
            for (int j = 0; j < num_vertices; ++j) {
                if (adjacencyMatrix[i][j] == INF)
                    cout << setw(5) << "INF";
                else
                    cout << setw(3) << adjacencyMatrix[i][j] << "  ";
            }
            cout << endl;
        }
    }

    int getWeight(int i, int j){
        return adjacencyMatrix[i][j];
    }


    int findSet(vector<int>& group, int v) {
        // Znajdowanie korzenia zbioru rozłącznego zawierającego wierzchołek
        if (group[v] != v) {
            group[v] = findSet(group, group[v]);
        }
        return group[v];
    }

    GraphMatrix getMinimumSpanningTreeKruskal() {
        // Nowy graf dla MST
        GraphMatrix mst(num_vertices, 0, 0);

        // Wektor wszystkich krawędzi w grafie
        vector<Edge> edges;

        // Tworzenie listy krawędzi na podstawie macierzy sąsiedztwa
        for (int i = 0; i < num_vertices; ++i) {
            for (int j = i + 1; j < num_vertices; ++j) {
                int weight = this->getWeight(i, j);
                if (weight != INF) {
                    edges.push_back(Edge(i, j, weight));
                }
            }
        }

        // Sortowanie krawędzie rosnąco według wagi, używając funkcji compareEdges
        sort(edges.begin(), edges.end(), Edge::compareEdges);


        // Inicjalizacja zbiorów rozłącznych dla każdego wierzchołka
        vector<int> group(num_vertices);
//        vector<int> rank(num_vertices, 0);

        // Inicjalizacja wektora grup
        for (int i = 0; i < num_vertices; ++i) {
            group[i] = i;
        }
        int sum = 0;
        // Przechodzenie po posortowanych krawędziach i dodawanie ich do MST
        for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;

            // Sprawdzenie, czy krawędź łączy dwa różne zbiory rozłączne
            int group_u = findSet(group, u);
            int group_v = findSet(group, v);

            if (group_u != group_v) {
                mst.addEdge(u, v, edge.weight, false);
                sum += edge.weight;
                group[group_u] = group_v;
            }
        }
        cout<<"Suma krawedzi w mst: "<<sum << endl;
        mst.displayMatrix();
        return mst;
    }

    GraphMatrix getMinimumSpanningTreePrim() {
        // Nowy graf dla MST
        GraphMatrix mst(num_vertices, 0, 0);

        // Wierzcholek od ktorego zaczynamy
        int startVertex = 0;

        vector<int> key(num_vertices, INF); // Tablica kluczy (wagi)
        vector<int> group(num_vertices, -1); // Tablica grup w MST
        vector<bool> inMST(num_vertices, false); // Tablica oznaczająca, czy wierzchołek należy już do MST

        // Ustawienie klucza startowego na 0
        key[startVertex] = 0;

        // Kolejka priorytetowa posortowana wg key
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, startVertex));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            // Przeszukiwanie sąsiadujących wierzchołków
            for (int v = 0; v < num_vertices; ++v) {
                int weight = this->getWeight(u, v);

                if (weight != INF && !inMST[v] && weight < key[v]) {
                    group[v] = u;
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                }
            }
        }
        int sum = 0;
        // Dodawanie krawędzi do MST w oparciu o tablicę grup
        for (int v = 0; v < num_vertices; ++v) {
            if (group[v] != -1) {
                mst.addEdge(v, group[v], key[v], false);
                sum += key[v];
            }
        }
        cout<<"Suma krawedzi w mst: "<<sum << endl;
        mst.displayMatrix();
        return mst;
    }

    static GraphMatrix graphMatrixloadFromFile(const string& fileName) {
        fstream file(fileName);
        int edges, vertices, u, v, weight, vf, vl;
        if(file.is_open())
        {
            bool directed = true;
            file >> vertices;
            file >> edges;
            file >> vf;
            file >> vl;
            if (vf == 0 && vl == 0){
                directed = false;
            }
            GraphMatrix graph = GraphMatrix(vertices, vf, vl);
            if(file.fail())
                cout << "File error - READ  num_vertices" << endl;
            else
                for(int i = 0; i < edges; i++)
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
                        graph.addEdge(u, v, weight, directed);
                }
            file.close();
            return graph;
        }
        else {
            cout << "File error - OPEN" << endl;
            GraphMatrix graph = GraphMatrix(vertices, 0, 0);
            return graph;
        }
    }
};