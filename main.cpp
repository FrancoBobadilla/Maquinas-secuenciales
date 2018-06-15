#include <iostream>
#include "AFD.h"
#include "APila.h"
#include "MTuring.h"
// o solo include de clase Automata abs?

#include "funcionesMain.h"

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

using namespace std;

int main() {
    holaExterno();
    cout << "Saliendo bien de main\n";

    char opcionMenu;

    do {
        cout << "MENU" << endl;
        cout << "\t0- Salir" << endl;
        cout << "\t1- Nuevo AFD" << endl;

        opcionMenu = leerOpciones("01", "Ingrese una de las opciones");

        switch (opcionMenu) {
            case '0':
                cout << "Saliendo" << endl;
                break;

            case '1':
                cout << "Opcion 1" << endl;

            default:
                break;
        }
    } while ('0' != opcionMenu);

    return 0;
}
