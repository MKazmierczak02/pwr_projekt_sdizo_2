//
// Created by ja on 2023-03-13.
//

#include <iostream>
#include "Handlers/GraphMatrixHandler.h"
#include "Handlers/GraphListHandler.h"

using namespace std;

void printMenu() {
    cout <<endl<<endl;
    cout << "1. Graf macierzy" << endl;
    cout << "2. Graf listy" << endl;
    cout << "0. Wyjdz" << endl;
}


int main() {
    cout << "Michal Kazmierczak"<<endl;
    cout << "Grupa: Wtorek 15:15, TN"<<endl;
    cout << "Projekt 2 Struktury danych i zlozonosc obliczeniowa";
    bool app = true;
    int choice;

    while (app) {
        printMenu();
        cin >> choice;
        switch (choice) {
            case 1: {
                GraphMatrixHandler::handle();
                break;
            }
            case 2: {
                GraphListHandler::handle();
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




