#include <iostream>

struct ListEl {
    ListEl* next;
    int v, weight;
};

class GraphMatrix {
private:
    int num_vertices;
    ListEl** adj_list;
    bool directed;
public:
    GraphMatrix(int num_vertices, bool directed) : num_vertices(num_vertices) {
        this->directed = directed;
        adj_list = new ListEl*[num_vertices];
        for (int i = 0; i < num_vertices; i++) {
            adj_list[i] = nullptr;
        }
    }

    void add_edge(int src, int dest, int weight) {
        if (src < 0 || src >= num_vertices || dest < 0 || dest >= num_vertices) {
//            throw std::out_of_range("Nieprawidlowy index wierzcholka");
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

    ~GraphMatrix() {
        for (int i = 0; i < num_vertices; i++) {
            ListEl* current = adj_list[i];
            while (current != nullptr) {
                ListEl* next = current->next;
                delete current;
                current = next;
            }
        }
        delete[] adj_list;
    }
};