//
// Created by nelon on 28/4/2018.
//

#ifndef AFD_APILA_H
#define AFD_APILA_H


#include "Data_Structures/Stack.h"
#include "Automata.h"

struct ElementosTransicionPila {
    Estado estado;
    bool conservarTope;
    char apilamiento;
};

class APila : public Automata {
private:
    // es una matriz cubica de punteros a estructura de estados y apilamientos (para que pueda ser null)
    ElementosTransicionPila ****f;

    unsigned int nroElementosAlfabetoPila;
    unsigned int cantActualElementosAlfabetoPila;
    char *alfabetoPila;
    char finDePila;

    Stack<char> *pila;

    //banderas
    bool tieneSimbolosPilaDefinidos;
    bool automataApagado;       // que tal ponerlo en la abs

    //métodos auxiliares
    unsigned int getAlfabetoPilaIndex(const char &simboloEntradaPila);

    Estado *buscarEstadoFinal();

    virtual void setAutomataListo();

public:

    APila(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoPila,
          char finDePila);
    virtual void transicion(char);

    void setF(std::string nombreEstadoSalida, char entrada, char valorPila, std::string nombreEstadoDestino,
              bool conservarTope, char apilamiento);

    void setAlfabetoPila(char);

    char getTopeDePila();

    void apagarAutomata();

    virtual std::string getExpresionFormal();

    unsigned int getNroElementosAlfabetoPila();
};


#endif //AFD_APILA_H


/*
 * El automata no tiene transiciones lambda
 * El automata no tiene transiciones "n-arias"
 *
 * Lo no determinista se reduce a no definir todas las transiciones
 *
 * */