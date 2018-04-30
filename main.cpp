#include <iostream>
//#include "AFD.h"
#include "APila.h"

using namespace std;

int main() {
    int pil = 0;                                                            //
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
        cout << endl << "Ingrese tamaño del alfabeto de entradas: ";
        cin >> ent;
        if (ent <= 0)
            cout << endl << "Ingrese una cantidad válida" << endl;
    }
    while (pil <= 0) {                                                      //
        cout << endl << "Ingrese tamaño del alfabeto de la pila: ";         //
        cin >> pil;                                                         //
        if (pil <= 0)                                                       //
            cout << endl << "Ingrese una cantidad válida" << endl;          //
    }
    //AFD A(est, ent);
    APila A(est, ent, pil);                                                 //
    char entrada = 'd';
    while (entrada != '/') {
        cout << endl << "Ingrese nueva entrada ('/' para terminar): ";
        cin >> entrada;
        if (entrada != '/') {
            try {
                A.transicion(entrada);
            } catch (int e) {
                if (e == -2) return 0;                                      //
                cout << endl << "Entrada inválida" << endl;
            }
        }
    }
    return 0;
}