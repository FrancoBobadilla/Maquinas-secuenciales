//
// Created by nelon on 28/4/2018.
//

#ifndef AFD_APILA_H
#define AFD_APILA_H


#include "Data_Structures/Stack.h"
#include "Estado.h"

struct EstadoYPila {
    Estado f_estado;
    char f_pila_1;//se apila primero
    char f_pila_2;
};

class APila {
private:
    int nE;
    Estado *est;

    int nEAlf;
    char *alf;

    Estado estAct;

    EstadoYPila ****f;  // es una matriz cubica de punteros a estructura de estados y apilamientos (para que pueda ser null)

    //Propios del Autómata de Pila
    Stack<char> pila;
    int nEAlfPila;
    char *alfPila;

    //métodos privados
    /*
    bool existeEntrada(char entrada);

    bool existeEntradaPila(char entradaPila);
     */

    int getEntradaIndex(char simboloEntrada);

    int getEntradaPilaIndex(char simboloEntradaPila);

public:
    APila(int nroEstados, int nroAlfEntrada, int nroAlfPila);

    void transicion(char);
};


#endif //AFD_APILA_H
