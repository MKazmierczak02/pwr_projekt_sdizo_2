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
            cout << "Nieprawidlowy index wierzcholka" << std::endl;
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
            std::cout << "Wierzcholek " << i << ": ";
            ListEl* current = adj_list[i];
            while (current != nullptr) {
                std::cout << "(" << current->v << ", " << current->weight << ") ";
                current = current->next;
            }
            std::cout << std::endl;
        }
    }


    int findSet(vector<int>& group, int vertex) {
        // Znajdź grupe wierzchołka (z kompresją ścieżki)
        if (group[vertex] != vertex) {
            group[vertex] = findSet(group, group[vertex]);
        }
        return group[vertex];
    }

    int getWeight(int u, int v) {
        return adj_list[u][v].weight;
    }

    GraphList getMinimumSpanningTreeKruskal() {
        // Nowy graf dla MST
        GraphList mst(num_vertices, 0, 0);

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

            // Jeśli dodanie krawędzi nie tworzy cyklu, dodaj ją do MST
            if (group_u != group_v) {
                mst.addEdge(u, v, edge.weight, false);
                sum += edge.weight;
                // Połącz zbiory wierzchołków źródłowego i docelowego
                group[group_u] = group_v;
            }
        }
        cout<<"Suma krawedzi w mst: "<<sum << endl;
        mst.displayList();
        return mst;
    }

    GraphList getMinimumSpanningTreePrim() {
        // Nowy graf dla MST
        GraphList mst(num_vertices, 0, 0);

        // Wierzcholek od ktorego zaczynamy
        int startVertex = 0;

        vector<int> key(num_vertices, INT_MAX); // Tablica kluczy (wagi)
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
        for (int v = 0; v < num_vertices; ++v) {
            if (group[v] != -1) {
                mst.addEdge(v, group[v], key[v], false);
                sum += key[v];
            }
        }
        cout<<"Suma krawedzi w mst: "<<sum << endl;
        mst.displayList();
        return mst;
    }


    static GraphList  graphListloadFromFile(const string& fileName) {
        fstream file(fileName);
        int edges, vertices, u, v, weight, vf, vl;
        if(file.is_open())
            fstream file(fileName);
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
            cout << directed;
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