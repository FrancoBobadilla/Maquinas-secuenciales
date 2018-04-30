//
// Created by nelon on 28/4/2018.
//

#ifndef AFD_APILA_H
#define AFD_APILA_H


#include "Data_Structures/Stack.h"
#include "Estado.h"

struct EstadoYPila {
    Estado f_estado;
    char f_pila;
    bool f_tope;
};

class APila {
private:
    Estado estAct;

    EstadoYPila ****f;  // es una matriz cubica de punteros a estructura de estados y apilamientos (para que pueda ser null)

    int nE;
    Estado *est;

    int nEAlf;
    char *alf;

    //Propios del Autómata de Pila
    int nEAlfPila;
    char *alfPila;

    Stack<char> pila;

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
