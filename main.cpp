#include <iostream>
#include "AFD.h"

using namespace std;

int main() {
    int est, ent;
    cout << "Ingrese número de estados: ";
    cin >> est;
    cout << endl << "Ingrese tamaño del alfabeto: ";
    cin >> ent;
    AFD A(est, ent);
    char entrada = 'd';
    while (entrada != '/') {
        cout << endl << "Ingrese nueva entrada ('/' para terminar): ";
        cin >> entrada;
        if (entrada != '/')
            A.transicion(entrada);

    }
    return 0;
}