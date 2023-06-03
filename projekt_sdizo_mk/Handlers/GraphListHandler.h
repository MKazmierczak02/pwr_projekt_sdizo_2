#include <iostream>
#include "../Structures/GraphList.cpp"
using namespace std;


class GraphListHandler {
public:
    static void printMenu(){
        cout <<endl<<"Graf Listy"<<endl;
        cout << "1. Wyswietl Graf" << endl;
        cout << "2. Dodaj krawedz" << endl;
        cout << "3. Wczytaj graf z pliku" << endl;
        cout << "4. Usun graf" << endl;
        cout << "5. Wyznacz MST (Kruskala)" <<endl;
        cout << "6. Wyznacz MST (Prima)" <<endl;
        cout << "7. Wyznacz Najkrotsze drogi w grafie (Djikstra)" <<endl;
        cout << "8. Wyznacz MST (Prima)" <<endl;
        cout << "0. Wyjdz" << endl;
    }

    static void handle() {
        bool app = true;
        int choice;

        int value, vf, vl;
        cout << endl << "Podaj ilosc wierzcholkow" <<endl;
        cin >> value;
        cout << endl << "Podaj wierzcholek poczatkowy" <<endl;
        cin >> vf;
        cout << endl << "Podaj wierzcholek koncowy" <<endl;
        cin >> vl;
        auto graph = GraphList(value, vf, vl);

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
                    cout << "Dodawanie grafu:" <<endl;
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
                    string file;
                    cout << endl << "Podaj sciezke do pliku" <<endl;
                    cin >> file;
                    graph = GraphList::graphListloadFromFile(file);
                    break;
                }
                case 4: {
                    graph.~GraphList();
                    cout << "Graf usuniety " << endl;
                    break;
                }
                case 5: {
                    graph.getMinimumSpanningTreeKruskal();
                    cout<< endl;
                    break;
                }
                case 6: {
                    graph.getMinimumSpanningTreePrim();
                    cout<< endl;
                    break;
                }
                case 7: {
                    graph.shortestPathDijkstra();
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
