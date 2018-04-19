#include <iostream>
#include "AFD.h"

using namespace std;

int main() {
    int est = 0, ent = 0;
    while (est <= 0) {
        cout << "Ingrese número de estados: ";
        cin >> est;
        if (est <= 0)
            cout << endl << "Ingrese una cantidad válida" << endl << endl;
    }
    cout << endl << "Estados del autómata:" << endl;
    for (int i = 0; i < est; ++i) {
        cout << " Estado " << i << endl;
    }
    while (ent <= 0) {
        cout << endl << "Ingrese tamaño del alfabeto: ";
        cin >> ent;
        if (ent <= 0)
            cout << endl << "Ingrese una cantidad válida" << endl;
    }
    AFD A(est, ent);
    char entrada = 'd';
    while (entrada != '/') {
        cout << endl << "Ingrese nueva entrada ('/' para terminar): ";
        cin >> entrada;
        if (entrada != '/') {
            try {
                A.transicion(entrada);
            } catch (int e) {
                cout << endl << "Entrada inválida" << endl;
            }
        }
    }
    return 0;
}