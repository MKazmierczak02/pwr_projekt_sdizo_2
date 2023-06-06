#include <iostream>
#include "../Structures/GraphList.cpp"
using namespace std;


class GraphListHandler {
public:
    static void printMenu(){
        cout <<endl<<"Graf Listy"<<endl;
        cout << "1. Wyswietl Graf" << endl;
        cout << "2. Dodaj krawedz" << endl;
        cout << "3. Wyznacz MST (Kruskala)" <<endl;
        cout << "4. Wyznacz MST (Prima)" <<endl;
        cout << "5. Wyznacz Najkrotsze drogi w grafie (Djikstra)" <<endl;
        cout << "6. Wyznacz Najkrotsze drogi w grafie (Bellman-Ford)" <<endl;
        cout << "0. Wyjdz" << endl;
    }

    static void handle() {
        bool app = true;
        int choice;

        vector<int> loaded_graph;

        string file;
        cout << endl << "Podaj sciezke do pliku" <<endl;
        cin >> file;
        auto graph = GraphList::graphListloadFromFile(file, false);
        while(app){
            printMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    cout << "Macierz grafu: " << endl;
                    graph.displayList();
                    cout << endl;
                    break;
                }
                case 2: {
                    bool directed;
                    int w1, w2, weight;
                    cout << "Dodawanie krawedzi:" <<endl;
                    cout << "Podaj pierwszy wierzcholek: " << endl;
                    cin >> w1;
                    cout << "Podaj drugi wierzcholek: " << endl;
                    cin >> w2;
                    cout << "Podaj wage krawdzi: " << endl;
                    cin >> weight;
                    cout << endl << "Czy krawedz ma byc skierowana? Y/N" <<endl;
                    char x;
                    cin >> x;
                    if (x=='Y' || x=='y'){
                        directed = true;
                    } else {
                        directed = false;
                    }
                    graph.addEdge(w1, w2, weight, directed);
                    break;
                }
                case 3: {
                    auto graphForAlgorithm = GraphList::graphListloadFromFile(file, false);
                    graphForAlgorithm.MinimumSpanningTreeKruskal();
                    cout<< endl;
                    break;
                }
                case 4: {
                    auto graphForAlgorithm = GraphList::graphListloadFromFile(file, false);
                    graphForAlgorithm.MinimumSpanningTreePrim();
                    cout<< endl;
                    break;
                }
                case 5: {
                    auto graphForAlgorithm = GraphList::graphListloadFromFile(file, true);
                    graphForAlgorithm.shortestPathDijkstra();
                    cout<< endl;
                    break;
                }
                case 6: {
                    auto graphForAlgorithm = GraphList::graphListloadFromFile(file, true);
                    graphForAlgorithm.shortestPathbellmanFord();
                    cout<< endl;
                    break;
                }
                case 0: {
                    app = false;
                    break;
                }
                default: {
                    cout << "Wpisano zly numer" << endl;
                    break;
                }
            }
        }

    }

};
