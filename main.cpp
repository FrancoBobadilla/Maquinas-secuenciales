#include <iostream>
#include "AFD.h"

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

using namespace std;

void cargarEstados(AFD *a) {
    Estado e;
    int tmp;
    char t;
    do {
        cout << "Ingresando nuevo Estado\n";
        cout << "\tNombre del Estado: ";
        LEERSTRING(e.nombre);

        do {
            cout << "\n\tIngrese 1 si es de salida (0 si no): ";
            cin >> tmp;
        } while (tmp != 0 && tmp != 1);
        e.situacion = (bool) tmp;

        try {
            a->setEstado(e);
        } catch (int exc) {
            if (-1 == exc)
                cout << "\n\tEl autómata ya tiene todos sus estados definidos\n";
            else {
                if (-2 == exc)
                    cout << "\n\tYa existe un Estado con el mismo nombre\n";
                else
                    cout << "\n\tERROR: " << exc << "\n";
            }
        }
        cout << "\nIngrese 1 para nuevo Estado o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
    //podria mostrarse cuantos se han ingresado y el la cant max de estados.
}

void cargarAlfabetoEntradas(AFD *a) {
    char n;
    int tmp;
    char t;

    cout << "Ingresar el alfabeto de Entrada" << endl;
    do {
        cout << "Ingresando nueva Entrada\n";
        cout << "\tSímbolo de entrada: ";
        cin >> n;

        try {
            a->setAlfabeto(n);
        } catch (int exc) {
            if (-1 == exc)
                cout << "\n\tEl autómata ya tiene su alfabeto de entrada definido\n";
            else {
                if (-2 == exc)
                    cout << "\n\tYa existe la entrada\n";
                else
                    cout << "\n\tERROR: " << exc << "\n";
            }
        }
        cout << "Ingrese 1 para nueva Entrada o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void cargarFTransicion(AFD *a) {
    char t, ent;
    string ESalida, EDestino;


    cout << "Ingresar Transiciones\n";
    do {
        cout << "Ingreando nueva Transicion\n";

        cout << "\tNombre del Estado del cual se parte: ";
        LEERSTRING(ESalida);

        cout << "\tSímbolo de entrada: ";
        cin >> ent;

        cout << "\tNombre del Estado al cual se llega: ";
        LEERSTRING(EDestino)

        try {
            a->setF(ESalida, ent, EDestino);
        } catch (int exc) {
            if (-11 == exc)
                cout << " \n\tNo existe un estado con el nombre " << ESalida << "\n";
            else {
                if (-12 == exc)
                    cout << "\n\t No existe un estado con el nombre " << EDestino << "\n";
                else {
                    if (-13 == exc)
                        cout << "\n\t No existe la entrada " << ent << "\n";
                    else {
                        if (-14 == exc)
                            cout << "\n\t Ya se ha definido la transicion previamente \n";
                        else
                            cout << "\n\t ERROR: " << exc << "\n";
                    }
                }
            }
        }
        cout << "Ingrese 1 para nueva Transicion o cualquier tecla para cancelar\n";
        cin >> t;
    } while ('1' == t);
}

void efectuarTransicion(AFD *a) {
    char ent;
    cout << "Efectuando nueva transicion\n";
    cout << "\tIngresar la entrada: ";
    cin >> ent;
    Estado tmp;
    try {
        tmp = a->transicion(ent);
    } catch (int exc) {
        if (-8 == exc)
            cout << " \n\tLa función de transicion no está completamente cargada\n";
        else {
            if (-21 == exc)
                cout << "\n\tLa entrada no es válida para el autómata\n";
            else
                cout << "ERROR: " << exc << "\n";
        }
    }

    cout << "Se ha alcanzado el estado: " << tmp.nombre << "\n";
    if (tmp.situacion) {
        cout << " \t SALIDA\n ";
    }
}

void cargarEstadoInicial(AFD *A) {
    std::string nom;
    cout << "Ingresando el Estado Inicial del Autómata\n";
    cout << "Ingrese el nombre del estado inicial\n";
    LEERSTRING(nom);

    try {
        A->setEstadoInicial(nom);
    } catch (int exc) {
        if (-1 == exc) {
            cout << "\nNo hay ningun estado con ese nombre\n";
            cargarEstadoInicial(A);
        } else
            cout << "\nERROR: " << exc << "\n";
    }
}

// todas estas funciones podrían formar parte de la clase Automata,
// proveen una forma estandar de interactuar con el automata.

void ProbarAFD();

int main() {
    ProbarAFD();
    return 0;
}


void ProbarAFD() {
    unsigned int cantEst, cantAlf;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;

    AFD A(cantEst, cantAlf);
    cout << "Cargando todos los estados\n";
    cargarEstados(&A);
    cout << "Cargando todas las entradas\n";
    cargarAlfabetoEntradas(&A);
    cout << "Cargando la función de transicion\n";
    cargarFTransicion(&A);
    cargarEstadoInicial(&A);

    char t;
    do {
        cout << "Efectuando transición\n";
        efectuarTransicion(&A);
        cout << "\nIngrese 1 si desea una nueva transicion\n";
        cin >> t;
    } while ('1' == t);
}