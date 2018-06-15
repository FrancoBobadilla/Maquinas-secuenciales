#include <iostream>
#include "AFD.h"
#include "APila.h"
#include "MTuring.h"
// o solo include de clase Automata abs?

#include "funcionesMain.h"
#include "ejemplosMain.h"

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

#define CLEAR

using namespace std;

void nuevoAFD();

void nuevoAPila();

void nuevoMTuring();

void ejemplos();

int main() {
    char opcionMenu;

    do {
        cout << "\n\nMENU PRINCIPAL" << endl;
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
                ejemplos();
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
        cout << "**************************************\n";

        switch (opcion) {
            case '0':
                cout << "Está por volver al menu principal, se perderá su automata\n";
                if ('0' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no"))
                    opcion = 'h';
                break;

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
                if ('1' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
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
    cout << " MENU PARA APila" << endl;
    cout << " Creando nuevo automata" << endl;
    unsigned int cantEst, cantAlf, cantPil;
    char finStack;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;
    cout << "Ingresar cantidad de elementos de pila del automata\n";
    cin >> cantPil;
    cout << "Ingresar el simbolo de fin de pila del automata\n";
    cin >> finStack;

    APila A(cantEst, cantAlf, cantPil, finStack);
    CLEAR;
    char opcion;

    do {
        cout << "\n\nAPila" << endl;
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
        cout << "\t4- Ingresar Simbolo de Entrada de Pila" << endl;
        cout << "\t5- Definir una transicion de la funcion" << endl;
        cout << "\t6- Ingresar una cadena para analizar" << endl;
        cout << "\t7- Hacer una transicion" << endl;
        cout << "\t8- Hacer todas las transiciones restantes" << endl;
        cout << "\t9- Mostrar estado actual" << endl;
        cout << "\ta- Reiniciar Automata" << endl;

        opcion = leerOpciones("0123456789a", "Ingrese una de las opciones");
        cout << "**************************************\n";

        switch (opcion) {
            case '0':
                cout << "Está por volver al menu principal, se perderá su automata\n";
                if ('0' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no"))
                    opcion = 'h';
                break;

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
                cargarSimboloPila(A);
                break;

            case '5':
                definirUnaTransicion(A);
                break;

            case '6':
                ingresarCadenaAnalizar(A);
                break;

            case '7':
                hacerUnaTransicion(A);
                break;

            case '8':
                hacerTodasTransiciones(A);
                break;

            case '9':
                mostrarSalida(A);
                break;

            case 'a':
                cout << "Está por reiniciar el autómata, se perderá su cadena de entrada\n"
                        "Los estados, entradas y funciones de transicion no se modificarán\n";
                if ('1' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
                    A.reiniciarAutomata();
                    cout << "Automata reiniciado\n";
                }
                break;

            default:
                break;
        }


    } while ('0' != opcion);
}

void nuevoMTuring() {
    cout << " MENU PARA MTuring" << endl;
    cout << " Creando nuevo automata" << endl;
    unsigned int cantEst, cantAlf, cantCin;
    char blanc;
    cout << "Ingresar cantidad de Estados del automata\n";
    cin >> cantEst;
    cout << "Ingresar cantidad de elementos de entrada del automata\n";
    cin >> cantAlf;
    cout << "Ingresar cantidad de elementos de cinta del automata\n";
    cin >> cantCin;
    cout << "Ingresar el simbolo de blanco de la cinta\n";
    cin >> blanc;

    MTuring A(cantEst, cantAlf, cantCin, blanc);
    CLEAR;
    char opcion;

    do {
        cout << "\n\nMTuring" << endl;
        cout << "La expresion de su automata es: " << A.getExpresionFormal() << endl << endl;
        cout << "La cinta es: " << A.getCopiaCinta();
        cout << "\nEl cabezal lee: " << A.getLecturaCabezal();

        if (A.tieneFuncionDeterminada())
            cout << "\nFuncion de transicion ya está determinada\n";
        else
            cout << "\nFuncion de transicion todavía no determinada\n";

        cout << "El autómata está ";
        if (A.isAutomataApagado())
            cout << "Apagado\n";
        else
            cout << "Encendido\n";

        cout << "\n\nMENU MTuring" << endl;
        cout << "\t0- Volver a menu principal" << endl;
        cout << "\t1- Ingresar Estado" << endl;
        cout << "\t2- Seleccionar Estado Inicial" << endl;
        cout << "\t3- Ingresar Simbolo de Entrada" << endl;
        cout << "\t4- Ingresar Simbolo de Entrada de Cinta" << endl;
        cout << "\t5- Definir una transicion de la funcion" << endl;
        cout << "\t6- Ingresar una cadena para analizar" << endl;
        cout << "\t7- Colocar cabezal en cinta" << endl;
        cout << "\t8- Hacer una transicion" << endl;
        cout << "\t9- Hacer todas las transiciones restantes" << endl;
        cout << "\ta- Mostrar estado actual" << endl;
        cout << "\tb- Reiniciar Automata" << endl;

        opcion = leerOpciones("0123456789ab", "Ingrese una de las opciones");
        cout << "**************************************\n";

        switch (opcion) {
            case '0':
                cout << "Está por volver al menu principal, se perderá su automata\n";
                if ('0' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no"))
                    opcion = 'h';
                break;

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
                cargarSimboloCinta(A);
                break;

            case '5':
                definirUnaTransicion(A);
                break;

            case '6':
                ingresarCadenaAnalizar(A);
                break;

            case '7':
                ponerCabezalCinta(A);
                break;

            case '8':
                hacerUnaTransicion(A);
                break;

            case '9':
                hacerTodasTransiciones(A);
                break;

            case 'a':
                mostrarSalida(A);
                break;

            case 'b':
                cout << "Está por reiniciar el autómata, se perderá su cadena de entrada\n"
                        "Los estados, entradas y funciones de transicion no se modificarán\n";
                if ('1' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
                    A.reiniciarAutomata();
                    cout << "Automata reiniciado\n";
                }
                break;

            default:
                break;
        }


    } while ('0' != opcion);
}

void ejemplos() {
    char opcionMenu;

    do {
        cout << "\n\nMENU de Ejemplos" << endl;
        cout << "\t0- Volver a Menu Principal" << endl;
        cout << "\t1- AFD que reconoce cadenas con un número impar de 'a' y par de 'b'" << endl;
        cout << "\t2- APila que reconoce si en dos nibbles separados por un * el primero tiene la misma "
                 "cantidad de 1 que el segundo de 0\n";
        cout << "\t3- MTuring que dado un numero binario precedido por $, escribe su siguiente" << endl;

        opcionMenu = leerOpciones("0123", "Ingrese una de las opciones");

        switch (opcionMenu) {
            case '0':
                break;

            case '1':
                ejemplo1();
                break;

            case '2':
                ejemplo2();
                break;

            case '3':
                ejemplo3();
                break;

            default:
                break;
        }
    } while ('0' != opcionMenu);
}