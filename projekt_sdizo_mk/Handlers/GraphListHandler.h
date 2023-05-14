#include <iostream>
#include "../Structures/GraphList.cpp"
using namespace std;


class GraphListHandler {

public:
    static void printMenu(){
        cout <<endl<<"Graf listy"<<endl;
        cout << "1. Wyswietl Graf" << endl;
        cout << "2. Dodaj krawedz" << endl;
        cout << "3. Wczytaj graf z pliku" << endl;
        cout << "4. Usun graf" << endl;
        cout << "0. Wyjdz" << endl;
    }

    static void handle() {
        bool app = true;
        int choice;

        int value;
        cout << endl << "Podaj ilosc wierzcholkow" <<endl;
        cin >> value;
        auto graph = GraphList(value);

        while(app){
            printMenu();
            cin >> choice;
            switch (choice) {
                case 1: {
                    cout << "Lista grafu: " << endl;
                    graph.displayList();
                    cout << endl;
                    break;
                }
                case 2: {
                    int w1, w2, weight;
                    cout << "Dodawanie grafu:" <<endl;
                    cout << "Podaj pierwszy wierzcholek: " << endl;
                    cin >> w1;
                    cout << "Podaj drugi wierzcholek: " << endl;
                    cin >> w2;
                    cout << "Podaj wage krawdzi: " << endl;
                    cin >> weight;
                    graph.addEdge(w1, w2, weight);
                    break;
                }
                case 3: {
                    string file;
                    cout << endl << "Podaj sciezke do pliku" <<endl;
                    cin >> file;
//                    graph.loadFromFile(file);
                    break;
                }
                case 4: {
                    graph.removeGraph();
                    cout << "Graf usuniety " << endl;
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
