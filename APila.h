//
// Created by nelon on 28/4/2018.
//

#ifndef AFD_APILA_H
#define AFD_APILA_H


#include "Data_Structures/Stack.h"
#include "Automata.h"

struct ElementosTransicionPila {
    Estado f_estado;
    char f_pila;
    bool f_tope;
};

class APila : public Automata {
private:
    // es una matriz cubica de punteros a estructura de estados y apilamientos (para que pueda ser null)
    ElementosTransicionPila ****f;

    //Propios del Autómata de Pila
    int nroElementosAlfabetoPila;
    char *alfabetoPila;

    Stack<char> pila;

    //métodos privados

    int getEntradaIndex(char simboloEntrada);

    int getEntradaPilaIndex(char simboloEntradaPila);

public:
    APila(unsigned int nroEstados, unsigned int nroAlfEntrada, unsigned int nroAlfPila);

   void transicion(char);
};


#endif //AFD_APILA_H
