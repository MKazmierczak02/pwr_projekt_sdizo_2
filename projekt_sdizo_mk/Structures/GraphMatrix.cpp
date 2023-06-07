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


class GraphMatrix {

private:
    int INF = numeric_limits<int>::max(); // Wartość reprezentująca brak krawędzi
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
        if (u < 0 || u >= num_vertices || v < 0 || v >= num_vertices){
            cout << "Nieprawidlowy index wierzcholka" << endl;
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
        for (int i = 0; i < num_vertices; i++) {cout << setw(5) << i;}
        cout << endl;
        for (int i = 0; i < num_vertices; i++) {
            cout << i << " ";
            for (int j = 0; j < num_vertices; j++) {
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

    void MinimumSpanningTreeKurskal() {
        // Wektor wszystkich krawędzi w grafie
        vector<Edge> edges;

        // Tworzenie listy krawędzi na podstawie macierzy sąsiedztwa
        for (int i = 0; i < num_vertices; i++) {
            for (int j = i + 1; j < num_vertices; j++) {
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
        for (int i = 0; i < num_vertices; i++) {
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

            // Jeśli nie wystąpi cykl, dodawanie do MST
            if (group_u != group_v) {
                cout << "(" <<v <<","<<u<<")  "<<edge.weight<<endl;
                sum += edge.weight;
                // Łączenie zbiorów
                group[group_u] = group_v;
            }
        }
        cout<<"MST = "<<sum << endl;
    }

    void MinimumSpanningTreePrim() {
        // Wierzcholek od ktorego zaczynamy
        int startVertex = 0;

        vector<int> key(num_vertices, INF); // Tablica kluczy (wagi)
        vector<int> group(num_vertices, -1); // Tablica grup w MST
        vector<bool> inMST(num_vertices, false); // Tablica wierzcholkow nalezacych MST

        // Ustawienie klucza startowego na 0
        key[startVertex] = 0;

        // Kolejka priorytetowa posortowana wg wag
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, startVertex));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            inMST[u] = true;

            // Przeszukiwanie sąsiadujących wierzchołków
            for (int v = 0; v < num_vertices; v++) {
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
        for (int v = 0; v < num_vertices; v++) {
            if (group[v] != -1) {
                cout << "(" <<v <<","<<group[v]<<")  "<<key[v]<<endl;
                sum += key[v];
            }
        }
        cout<<"MST = "<<sum << endl;
    }

    void shortestPathDijkstra() {
        vector<int> distance(num_vertices, INF);  // Tablica odległości
        vector<int> parent(num_vertices, -1);     // Tablica poprzednikow w najkrótszej ścieżce
        vector<bool> visited(num_vertices, false); // Tablica odwiedzonych wierzchołków

        int startVertex = this->vf;
        // Odległość od wierzchołka początkowego do samego siebie wynosi 0
        distance[startVertex] = 0;

        for (int i = 0; i < num_vertices - 1; i++) {
            int minDistance = INF;
            int minVertex = -1;

            // Znalezienie wierzchołka o najmniejszej odległości
            for (int v = 0; v < num_vertices; v++) {
                if (!visited[v] && distance[v] < minDistance) {
                    minDistance = distance[v];
                    minVertex = v;
                }
            }
            // Jeśli nie znaleziono żadnego wierzchołka, przerywamy
            if (minVertex == -1)
                break;

            visited[minVertex] = true;

            // Aktualizacja odległości do sąsiadujących wierzchołków
            for (int v = 0; v < num_vertices; v++) {
                int weight = this->getWeight(minVertex, v);
                if (weight < 0) {
                    cout << endl << "ERROR: Graf posiada krawędzie ujemnej wagi" << endl;
                    return;
                }
                if (weight != INF && !visited[v] && distance[minVertex] + weight < distance[v]) {
                    distance[v] = distance[minVertex] + weight;
                    parent[v] = minVertex;
                }
            }
        }

        cout << "Start = " << startVertex<< endl;
        cout << "End  Dist Path"<< endl;

        // Wyświetlenie długości drogi i sekwencji wierzchołków dla każdego wierzchołka
        for (int v = 0; v < num_vertices; v++) {
            if (v != startVertex) {
                cout << v << "  |  ";
                cout << distance[v] << "  |  ";

                vector<int> path;
                int currentVertex = v;
                while (currentVertex != -1) {
                    path.push_back(currentVertex);
                    currentVertex = parent[currentVertex];
                }

                for (int i = path.size() - 1; i >= 0; --i) {
                    cout << path[i];
                    if (i != 0)
                        cout << " ";
                }
                cout << endl;
            }
        }
    }

    void shortestPathBellmanFord() {
        int startVertex = this->vf;

        vector<int> distance(num_vertices, INF); // Tablica odległości
        distance[startVertex] = 0;
        vector<int> parent(num_vertices, -1); // Tablica poprzedników w najkrótszej ścieżce

        // Relaksacja krawędzi |V|
        for (int i = 0; i < num_vertices - 1; i++) {
            // Przejście przez wszystkie krawędzie i aktualizacja odległości
            for (int u = 0; u < num_vertices; u++) {
                for (int v = 0; v < num_vertices; v++) {
                    int weight = this->getWeight(u, v);
                    if (weight != INF && distance[u] != INF && distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;
                        parent[v] = u;
                    }
                }
            }
        }

        // Sprawdzenie ujemnych cykli
        for (int u = 0; u < num_vertices; u++) {
            for (int v = 0; v < num_vertices; v++) {
                int weight = this->getWeight(u, v);
                if (weight != INF && distance[u] != INF && distance[u] + weight < distance[v]) {
                    cout << "Graf zawiera ujemny cykl" << endl;
                    return;
                }
            }
        }

        // Wyświetlenie wyników
        cout << "Start = " << startVertex<< endl;
        cout << "End  Dist Path"<< endl;

        for (int v = 0; v < num_vertices; v++) {
            if (v != startVertex) {

                cout << v << "  |  ";
                if (distance[v] == INF) {
                    cout << "Brak drogi." << endl;
                } else {
                    cout << distance[v] << "  | ";
                }
                    vector<int> path;
                    int currentVertex = v;
                    while (currentVertex != -1) {
                        path.push_back(currentVertex);
                        currentVertex = parent[currentVertex];
                    }
                    // Wyswietlanie drogi od tylu
                    for (int i = path.size() - 1; i >= 0; i--) {
                        cout << path[i];
                        if (i != 0)
                            cout << " ";
                    }
                    cout << endl;
            }
        }
    }

    static GraphMatrix graphMatrixloadFromFile(const string& fileName, bool directed) {
        fstream file(fileName);
        int edges, vertices, u, v, weight, vf, vl;
        if(file.is_open())
        {
            file >> edges;
            file >> vertices;
            file >> vf;
            file >> vl;
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