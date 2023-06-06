#include <iostream>
#include "../Structures/GraphMatrix.cpp"
using namespace std;


class GraphMatrixHandler {

public:
    static void printMenu(){
        cout <<endl<<"Graf macierzy"<<endl;
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
        string file;
        cout << endl << "Podaj sciezke do pliku" <<endl;
        cin >> file;
        auto graph = GraphMatrix::graphMatrixloadFromFile(file, false);

        while(app){
            printMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    cout << "Macierz grafu: " << endl;
                    graph.displayMatrix();
                    cout << endl;
                    break;
                }
                case 2: {
                    int w1, w2, weight;
                    bool directed;
                    cout << "Dodawanie krawedzi:" <<endl;
                    cout << "Podaj pierwszy wierzcholek: " << endl;
                    cin >> w1;
                    cout << "Podaj drugi wierzcholek: " << endl;
                    cin >> w2;
                    cout << "Podaj wage krawdzi: " << endl;
                    cin >> weight;
                    cout << endl << "Czy graf ma byc skierowany? Y/N" <<endl;
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
                    auto graphForAlgorithm = GraphMatrix::graphMatrixloadFromFile(file, false);
                    graphForAlgorithm.MinimumSpanningTreeKurskal();
                    cout<< endl;
                    break;
                }
                case 4: {
                    auto graphForAlgorithm = GraphMatrix::graphMatrixloadFromFile(file, false);
                    graphForAlgorithm.MinimumSpanningTreePrim();
                    cout<< endl;
                    break;
                }
                case 5: {
                    auto graphForAlgorithm = GraphMatrix::graphMatrixloadFromFile(file, true);
                    graphForAlgorithm.shortestPathDijkstra();
                    cout<< endl;
                    break;
                }
                case 6: {
                    auto graphForAlgorithm = GraphMatrix::graphMatrixloadFromFile(file, true);
                    graphForAlgorithm.shortestPathBellmanFord();
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
