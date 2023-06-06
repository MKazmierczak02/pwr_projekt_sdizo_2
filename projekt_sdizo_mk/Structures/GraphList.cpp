#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

class EdgeList {
public:
    int u, v, weight;

    EdgeList(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    static bool compareEdges(const EdgeList& e1, const EdgeList& e2) {
        return e1.weight < e2.weight;
    }
};

struct ListEl {
    ListEl* next;
    int v, weight;
};

class GraphList {
private:
    int INF = numeric_limits<int>::max();
    int num_vertices, vf, vl;
    ListEl** adj_list;

public:
    GraphList(int num_vertices, int vf, int vl)  {
        this->num_vertices = num_vertices;
        this->vf = vf;
        this->vl = vl;
        adj_list = new ListEl*[num_vertices];
        for (int i = 0; i < num_vertices; i++) {
            adj_list[i] = nullptr;
        }
    }

    void addEdge(int u, int v, int weight, bool directed) {
        if (u < 0 || u >= num_vertices || v < 0 || v >= num_vertices) {
            cout << "Nieprawidlowy index wierzcholka" << endl;
            return;
        }

        ListEl* new_edge = new ListEl;
        new_edge->v = v;
        new_edge->weight = weight;
        new_edge->next = adj_list[u];
        adj_list[u] = new_edge;

        // Dodanie krawędzi v -> u (dla nieskierowanego grafu)
        if (!directed) {
            new_edge = new ListEl;
            new_edge->v = u;
            new_edge->weight = weight;
            new_edge->next = adj_list[v];
            adj_list[v] = new_edge;
        }
    }



    void displayList() {
        for (int i = 0; i < num_vertices; i++) {
            cout << "Wierzcholek " << i << ": ";
            ListEl* current = adj_list[i];
            while (current != nullptr) {
                cout << "(" << current->v << ", " << current->weight << ") ";
                current = current->next;
            }
            cout << endl;
        }
    }


    int findSet(vector<int>& group, int vertex) {
        // Znajdź grupe wierzchołka (z kompresją ścieżki)
        if (group[vertex] != vertex) {
            group[vertex] = findSet(group, group[vertex]);
        }
        return group[vertex];
    }

    void MinimumSpanningTreeKruskal() {
        // Wektor wszystkich krawędzi w grafie
        vector<EdgeList> edges;

        // Tworzenie listy krawędzi na podstawie listy sąsiedztwa
        for (int i = 0; i < num_vertices; i++) {
            ListEl* current = adj_list[i];
            while (current != nullptr) {
                int v = current->v;
                int weight = current->weight;
                edges.push_back(EdgeList(i, v, weight));
                current = current->next;
            }
        }

        // Sortowanie krawędzie rosnąco według wagi, używając funkcji compareEdges
        sort(edges.begin(), edges.end(), EdgeList::compareEdges);

        // Inicjalizacja zbiorów rozłącznych dla każdego wierzchołka
        vector<int> group(num_vertices);

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
            ListEl* current = adj_list[u];
            while (current != nullptr) {
                int v = current->v;
                int weight = current->weight;

                if (!inMST[v] && weight < key[v]) {
                    group[v] = u;
                    key[v] = weight;
                    pq.push(make_pair(key[v], v));
                }

                current = current->next;
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
        vector<int> distance(num_vertices, INF);    // Tablica odległości
        vector<int> parent(num_vertices, -1);   // Tablica poprzednikow w najkrótszej ścieżce
        vector<bool> visited(num_vertices, false);  // Tablica odwiedzonych wierzchołków

        int startVertex = this->vf;
        // Odległość od wierzchołka początkowego do samego siebie wynosi 0
        distance[startVertex] = 0;

        for (int i = 0; i < num_vertices; i++) {
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
            if (minVertex == -1) {
                break;
            }

            visited[minVertex] = true;

            // Aktualizacja odległości do sąsiadujących wierzchołków
            ListEl* current = adj_list[minVertex];
            while (current != nullptr) {
                int v = current->v;
                int weight = current->weight;
                if (weight != INF && distance[minVertex] + weight < distance[v]) {
                    distance[v] = distance[minVertex] + weight;
                    parent[v] = minVertex;
                }

                current = current->next;
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

    void shortestPathbellmanFord() {
        int startVertex = this->vf;

        vector<int> distance(num_vertices, INF); // Tablica odległości
        distance[startVertex] = 0;
        vector<int> parent(num_vertices, -1); // Tablica poprzednikow w najkrótszej ścieżce

        // Relaksacja krawędzi |V|
        for (int i = 0; i < num_vertices - 1; i++) {
            // Iteracja po wszystkich krawędziach
            for (int u = 0; u < num_vertices; u++) {
                ListEl* current = adj_list[u];
                while (current != nullptr) {
                    int v = current->v;
                    int weight = current->weight;

                    // Relaksacja krawędzi
                    if (distance[u] != INF && distance[u] + weight < distance[v]) {
                        distance[v] = distance[u] + weight;
                        parent[v] = u;
                    }
                    current = current->next;
                }
            }
        }

        // Sprawdzenie czy występują ujemne cykle
        for (int u = 0; u < num_vertices; u++) {
            ListEl* current = adj_list[u];
            while (current != nullptr) {
                int v = current->v;
                int weight = current->weight;

                // Sprawdzenie ujemnego cyklu
                if (distance[u] != INF && distance[u] + weight < distance[v]) {
                    cout << "Graf zawiera ujemny cykl." << endl;
                    return;
                }
                current = current->next;
            }
        }

        // Wyświetlenie wyników
        cout << "Start = " << startVertex<< endl;
        cout << "End  Dist Path"<< endl;

        for (int v = 0; v < num_vertices; v++) {
            if (v!=startVertex){
                cout << v << "  |  ";
                if (distance[v] == INF) {
                    cout << "Brak ścieżki." << endl;
                } else {
                    cout << distance[v] << "  | ";
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
    }

    static GraphList  graphListloadFromFile(const string& fileName) {
        fstream file(fileName);
        int edges, vertices, u, v, weight, vf, vl;
        if(file.is_open())
            fstream file(fileName);
        if(file.is_open())
        {
            bool directed = true;
            file >> edges;
            file >> vertices;
            file >> vf;
            file >> vl;
            if (vf == 0 && vl == 0){
                directed = false;
            }
            GraphList graph = GraphList(vertices, vf, vl);
            if(file.fail())
                cout << "File error - READ SIZE" << endl;
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
            return {vertices, 0, 0};
        }
    }

};