//
// Created by nelon on 6/15/2018.
//

#ifndef AFD_EJEMPLOSMAIN_H
#define AFD_EJEMPLOSMAIN_H

#include <iostream>
#include "Automata.h"
#include "AFD.h"
#include "APila.h"
#include "MTuring.h"
#include "funcionesMain.h"

#define LEERSTRING(X) fflush(stdin); cin >> X; fflush(stdin);

using namespace std;

void ejemplo1() {
    cout << "AFD que reconoce cadenas con un número impar de 'a' y par de 'b'\n";

    AFD W(4, 2);

    //sript para automata
    W.setEstado("C0", false);
    W.setEstado("C1", false);
    W.setEstado("C2", false);
    W.setEstado("C3", true);

    W.setAlfabeto('a');
    W.setAlfabeto('b');

    W.setF("C0", 'a', "C3");
    W.setF("C0", 'b', "C1");

    W.setF("C1", 'a', "C2");
    W.setF("C1", 'b', "C0");

    W.setF("C2", 'a', "C1");
    W.setF("C2", 'b', "C3");

    W.setF("C3", 'a', "C0");
    W.setF("C3", 'b', "C2");

    W.setEstadoInicial("C0");

    char opcion;

    do {
        cout << "\n\nAFD";
        cout << " \tReconoce cadenas con un número impar de 'a' y par de 'b'\n";
        cout << "La expresion de su automata es: " << W.getExpresionFormal() << endl << endl;

        cout << "El autómata está ";
        if (W.isAutomataApagado())
            cout << "Apagado\n";
        else
            cout << "Encendido\n";

        cout << "\n\nMENU" << endl;
        cout << "\t0- Volver a menu principal" << endl;
        cout << "\t1- Ingresar una cadena para analizar" << endl;
        cout << "\t2- Hacer una transicion" << endl;
        cout << "\t3- Hacer todas las transiciones restantes" << endl;
        cout << "\t4- Mostrar estado actual" << endl;
        cout << "\t5- Reiniciar Automata" << endl;

        opcion = leerOpciones("012345", "Ingrese una de las opciones");
        cout << "**************************************\n";

        switch (opcion) {
            case '0':
                cout << "Está por volver al menu de ejemplos, se perderá su automata\n";
                if ('0' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no"))
                    opcion = 'h';
                break;

            case '1':
                ingresarCadenaAnalizar(W);
                break;

            case '2':
                hacerUnaTransicion(W);
                break;

            case '3':
                hacerTodasTransiciones(W);
                break;

            case '4':
                mostrarSalida(W);
                break;

            case '5':
                cout << "Está por reiniciar el autómata, se perderá su cadena de entrada\n"
                        "Los estados, entradas y funciones de transicion no se modificarán\n";
                if ('1' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
                    W.reiniciarAutomata();
                    cout << "Automata reiniciado\n";
                }
                break;

            default:
                break;
        }
    } while ('0' != opcion);
}

void ejemplo2() {
    cout << "APila que reconoce si en dos nibbles separados por un * el primero tiene la misma "
            "cantidad de 1 que el segundo de 0\n";

    APila S(4, 3, 1, '#');

    // script automata
    S.setEstado("q0", false);
    S.setEstado("q1", false);
    S.setEstado("q2", false);
    S.setEstado("q3", true);

    S.setEstadoInicial("q0");

    S.setAlfabeto('0');
    S.setAlfabeto('1');
    S.setAlfabeto('*');

    S.setAlfabetoPila('a');

    S.setF("q0", '0', '#', "q0", true, (char) 0);
    S.setF("q0", '0', 'a', "q0", true, (char) 0);
    S.setF("q0", '1', '#', "q1", true, 'a');
    S.setF("q0", '*', '#', "q2", true, (char) 0);
    S.setF("q0", '*', 'a', "q2", true, (char) 0);

    S.setF("q1", '1', 'a', "q1", true, 'a');
    S.setF("q1", '0', 'a', "q1", true, (char) 0);
    S.setF("q1", '*', 'a', "q2", true, (char) 0);

    S.setF("q2", '0', 'a', "q2", false, (char) 0);
    S.setF("q2", '1', 'a', "q2", true, (char) 0);
    S.setF("q2", '1', '#', "q2", true, (char) 0);


    char opcion;

    do {
        cout << "\n\nAPila";
        cout << " \tReconoce los nibbles separados por *\n";
        cout << "La expresion de su automata es: " << S.getExpresionFormal() << endl << endl;

        cout << "El autómata está ";
        if (S.isAutomataApagado())
            cout << "Apagado\n";
        else
            cout << "Encendido\n";

        cout << "\n\nMENU" << endl;
        cout << "\t0- Volver a menu principal" << endl;
        cout << "\t1- Ingresar una cadena para analizar" << endl;
        cout << "\t2- Hacer una transicion" << endl;
        cout << "\t3- Hacer todas las transiciones restantes" << endl;
        cout << "\t4- Mostrar estado actual" << endl;
        cout << "\t5- Reiniciar Automata" << endl;

        opcion = leerOpciones("012345", "Ingrese una de las opciones");
        cout << "**************************************\n";

        switch (opcion) {
            case '0':
                cout << "Está por volver al menu de ejemplos, se perderá su automata\n";
                if ('0' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no"))
                    opcion = 'h';
                break;

            case '1':
                ingresarCadenaAnalizar(S);
                break;

            case '2':
                hacerUnaTransicion(S);
                break;

            case '3':
                hacerTodasTransiciones(S);
                break;

            case '4':
                mostrarSalida(S);
                break;

            case '5':
                cout << "Está por reiniciar el autómata, se perderá su cadena de entrada\n"
                        "Los estados, entradas y funciones de transicion no se modificarán\n";
                if ('1' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
                    S.reiniciarAutomata();
                    cout << "Automata reiniciado\n";
                }
                break;

            default:
                break;
        }
    } while ('0' != opcion);
}

void ejemplo3() {
    cout << "\tMTuring que dado un numero binario precedido por $, escribe su siguiente" << endl;

    //script automata
    MTuring Q(6, 3, 3, 'b');
    Q.setEstado("q0", false);
    Q.setEstado("q1", false);
    Q.setEstado("q2", false);
    Q.setEstado("q3", false);
    Q.setEstado("q4", true);
    Q.setEstado("q5", false);

    Q.setEstadoInicial("q0");

    Q.setAlfabeto('0');
    Q.setAlfabeto('1');
    Q.setAlfabeto('$');
    Q.setAlfabetoCinta('0');
    Q.setAlfabetoCinta('1');
    Q.setAlfabetoCinta('$');

    Q.setF("q0", '0', "q0", 'd', '0');
    Q.setF("q0", '1', "q0", 'd', '1');
    Q.setF("q0", 'b', "q1", 'i', 'b');
    Q.setF("q0", '$', "q0", 'd', '$');

    Q.setF("q1", '0', "q2", 'i', '1');
    Q.setF("q1", '1', "q3", 'i', '0');

    Q.setF("q2", '0', "q2", 'i', '0');
    Q.setF("q2", '1', "q2", 'i', '1');
    Q.setF("q2", '$', "q5", 'd', '$');

    Q.setF("q3", '0', "q2", 'i', '1');
    Q.setF("q3", '1', "q3", 'i', '0');
    Q.setF("q3", '$', "q4", 'p', '1');

    Q.setF("q5", '0', "q4", 'p', '0');
    Q.setF("q5", '1', "q4", 'p', '1');

    char opcion;

    do {
        cout << "\n\nMturing";
        cout << " \tEscribe el siguiente de un $binario\n";
        cout << "La expresion de su automata es: " << Q.getExpresionFormal() << endl << endl;

        cout << "El autómata está ";
        if (Q.isAutomataApagado())
            cout << "Apagado\n";
        else
            cout << "Encendido\n";

        cout << "\n\nMENU" << endl;
        cout << "\t0- Volver a menu principal" << endl;
        cout << "\t1- Ingresar una cadena para analizar" << endl;
        cout << "\t2- Hacer una transicion" << endl;
        cout << "\t3- Hacer todas las transiciones restantes" << endl;
        cout << "\t4- Poner Cabezal" << endl;
        cout << "\t5- Mostrar estado actual" << endl;
        cout << "\t6- Reiniciar Automata" << endl;

        opcion = leerOpciones("0123456", "Ingrese una de las opciones");
        cout << "**************************************\n";

        switch (opcion) {
            case '0':
                cout << "Está por volver al menu de ejemplos, se perderá su automata\n";
                if ('0' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no"))
                    opcion = 'h';
                break;

            case '1':
                ingresarCadenaAnalizar(Q);
                break;

            case '2':
                hacerUnaTransicion(Q);
                break;

            case '3':
                hacerTodasTransiciones(Q);
                break;

            case '4':
                ponerCabezalCinta(Q);
                break;

            case '5':
                mostrarSalida(Q);
                break;

            case '6':
                cout << "Está por reiniciar el autómata, se perderá su cadena de entrada\n"
                        "Los estados, entradas y funciones de transicion no se modificarán\n";
                if ('1' == leerOpciones("01", "Está seguro? 1 para sí o 0 para no")) {
                    Q.reiniciarAutomata();
                    cout << "Automata reiniciado\n";
                }
                break;

            default:
                break;
        }
    } while ('0' != opcion);
}


#endif //AFD_EJEMPLOSMAIN_H
