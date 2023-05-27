#include <iostream>

struct ListEl {
    ListEl* next;
    int v, weight;
};

class GraphList {
private:
    int num_vertices;
    ListEl** adj_list;
    bool directed;
public:
    GraphList(int num_vertices, bool directed) : num_vertices(num_vertices) {
        this->directed = directed;
        adj_list = new ListEl*[num_vertices];
        for (int i = 0; i < num_vertices; i++) {
            adj_list[i] = nullptr;
        }
    }

    void addEdge(int src, int dest, int weight) {
        if (src < 0 || src >= num_vertices || dest < 0 || dest >= num_vertices) {
            std::cout <<"Nieprawidlowy index wierzcholka" << std::endl;
            return;
        }

        ListEl* new_edge = new ListEl;
        new_edge->v = dest;
        new_edge->weight = weight;
        new_edge->next = adj_list[src];
        adj_list[src] = new_edge;

        // Dodaj krawędź dest -> src (nieskierowany graf)
        if (!directed) {
            new_edge = new ListEl;
            new_edge->v = src;
            new_edge->weight = weight;
            new_edge->next = adj_list[dest];
            adj_list[dest] = new_edge;
        }
    }

    void print_graph() {
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

//    ~GraphList() {
//        for (int i = 0; i < num_vertices; i++) {
//            ListEl* current = adj_list[i];
//            while (current != nullptr) {
//                ListEl* next = current->next;
//                delete current;
//                current = next;
//            }
//        }
//        delete[] adj_list;
//    }

    int findParent(std::vector<int>& parent, int vertex) {
        // Znajdź rodzica wierzchołka (z kompresją ścieżki)
        if (parent[vertex] != vertex) {
            parent[vertex] = findParent(parent, parent[vertex]);
        }
        return parent[vertex];
    }

    GraphList getMinimumSpanningTree() {
        // nowy graf dla MST
        GraphList mst(num_vertices, directed);

        // wektor wszystkich krawędzi w grafie
        std::vector<std::pair<int, std::pair<int, int>>> edges;

        // Przejdź przez listę sąsiedztwa i dodaj krawędzie do wektora
        for (int i = 0; i < num_vertices; i++) {
            ListEl* current = adj_list[i];
            while (current != nullptr) {
                int dest = current->v;
                int weight = current->weight;
                edges.push_back(std::make_pair(weight, std::make_pair(i, dest)));
                current = current->next;
            }
        }

        // Posortuj krawędzie rosnąco według wagi
        std::sort(edges.begin(), edges.end());

        // Utwórz wektor do śledzenia rodzica każdego wierzchołka
        std::vector<int> parent(num_vertices);

        // Zainicjalizuj wektor rodziców
        for (int i = 0; i < num_vertices; i++) {
            parent[i] = i;
        }

        // Przetwarzaj każdą krawędź w posortowanej kolejności
        for (auto edge : edges) {
            int src = edge.second.first;
            int dest = edge.second.second;

            // Znajdź rodzica wierzchołków źródłowego i docelowego
            int parent_src = findParent(parent, src);
            int parent_dest = findParent(parent, dest);

            // Jeśli dodanie krawędzi nie tworzy cyklu, dodaj ją do MST
            if (parent_src != parent_dest) {
                mst.addEdge(src, dest, edge.first);

                // Połącz zbiory wierzchołków źródłowego i docelowego
                parent[parent_src] = parent_dest;
            }
        }

        return mst;
    }

    static GraphList graphListloadFromFile(const std::string& fileName) {
        std::fstream file(fileName);
        int size;
        int u, v, weight;
        if(file.is_open())
        {
            file >> size;
            GraphList graph = GraphList(size, false);
            if(file.fail())
                std::cout << "File error - READ SIZE" << endl;
            else
                while (!file.eof())
                {
                    file >> u;
                    file >> v;
                    file >> weight;
                    if(file.fail())
                    {
                        std::cout << "File error - READ DATA" << endl;
                        break;
                    }
                    else
                        graph.addEdge(u, v, weight);
                }
            file.close();
            return graph;
        }
        else
            std::cout << "File error - OPEN" << endl;
    }
};