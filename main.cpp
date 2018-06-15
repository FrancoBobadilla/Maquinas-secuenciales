#include <iostream>
#include "AFD.h"
#include "APila.h"
#include "MTuring.h"
// o solo include de clase Automata abs?

#include "funcionesMain.h"

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

#define CLEAR

using namespace std;

void nuevoAFD();

void nuevoAPila();

void nuevoMTuring();

int main() {
    holaExterno();
    cout << "Saliendo bien de main\n";

    char opcionMenu;

    do {
        cout << "MENU" << endl;
        cout << "\t0- Salir" << endl;
        cout << "\t1- Nuevo AFD" << endl;
        cout << "\t2- Nuevo APila" << endl;
        cout << "\t3- Nuevo MTuring" << endl;
        cout << "\t4- Ejemplos" << endl;

        opcionMenu = leerOpciones("01234", "Ingrese una de las opciones");

        switch (opcionMenu) {
            case '0':
                cout << "Saliendo" << endl;
                break;

            case '1':
                cout << "Nuevo AFD" << endl;
                nuevoAFD();
                break;

            case '2':
                cout << "Nuevo APila" << endl;
                nuevoAPila();
                break;

            case '3':
                cout << "Nuevo MTuring" << endl;
                nuevoMTuring();
                break;

            case '4':
                cout << "Ejemplos" << endl;
                break;

            default:
                break;
        }
    } while ('0' != opcionMenu);

    return 0;
}

void nuevoAFD() {
    cout << " MENU PARA AFD" << endl;
    cout << " Creando nuevo automata" << endl;
    unsigned int cantEst, cantAlf;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;

    AFD A(cantEst, cantAlf);
    CLEAR;
    char opcion;

    do {
        cout << "\n\nAFD" << endl;
        cout << "La expresion de su automata es: " << A.getExpresionFormal() << endl << endl;

        if (A.tieneFuncionDeterminada())
            cout << "Funcion de transicion ya está determinada\n";
        else
            cout << "Funcion de transicion todavía no determinada\n";

        cout << "El autómata está ";
        if (A.isAutomataApagado())
            cout << "Apagado\n";
        else
            cout << "Encendido\n";

        cout << "\n\nMENU AFD" << endl;
        cout << "\t0- Volver a menu principal" << endl;
        cout << "\t1- Ingresar Estado" << endl;
        cout << "\t2- Seleccionar Estado Inicial" << endl;
        cout << "\t3- Ingresar Simbolo de Entrada" << endl;
        cout << "\t4- Definir una transicion de la funcion" << endl;
        cout << "\t5- Ingresar una cadena para analizar" << endl;
        cout << "\t6- Hacer una transicion" << endl;
        cout << "\t7- Hacer todas las transiciones restantes" << endl;
        cout << "\t8- Mostrar estado actual" << endl;
        cout << "\t9- Reiniciar Automata" << endl;

        opcion = leerOpciones("0123456789", "Ingrese una de las opciones");

        switch (opcion) {
            case '1':
                cargarEstado(A);
                break;

            case '2':
                cargarEstadoInicial(A);
                break;

            case '3':
                cargarSimboloEntrada(A);
                break;

            case '4':
                definirUnaTransicion(A);
                break;

            case '5':
                ingresarCadenaAnalizar(A);
                break;

            case '6':
                hacerUnaTransicion(A);
                break;

            case '7':
                hacerTodasTransiciones(A);
                break;

            case '8':
                mostrarSalida(A);
                break;

            case '9':
                cout << "Está por reiniciar el autómata, se perderá su cadena de entrada\n"
                        "Los estados, entradas y funciones de transicion no se modificarán\n";
                if (leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
                    A.reiniciarAutomata();
                    cout << "Automata reiniciado\n";
                }
                break;

            default:
                break;
        }


    } while ('0' != opcion);


}

void nuevoAPila() {

}

void nuevoMTuring() {

}