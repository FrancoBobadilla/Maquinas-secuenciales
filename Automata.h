//
// Created by nelon on 5/4/2018.
//

#ifndef AFD_AUTOMATA_H
#define AFD_AUTOMATA_H

#include "Estado.h"

class Automata {
protected:
    unsigned int nroEstados;
    unsigned int cantActualEstados;
    Estado *estados;
    Estado estadoActual;            // por que no pointer? const ptr o ptr const

    unsigned int nroElementosAlfabeto;
    unsigned int cantActualElementosAlfabeto;
    char *alfabeto;

    bool isCargado;

    //metodos auxiliares
    unsigned int getEstadoIndex(std::string nombreEstado);     // esto esta mal, deberia devolver unsigned int

    unsigned int getAlfabetoIndex(char elementoAlfabeto);

public:
    Automata(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    virtual Estado transicion(char) =0;
    // como hacer para que las funciones derivadas deban implementarla con distintos parametros;

    unsigned int getNroEstados() const;

    void setEstado(Estado);

protected:
    void setEstadoActual(std::string nombreEstado);

public:
    std::string getEstadoActual() const;

    unsigned int getNroElementosAlfabeto() const;

    void setAlfabeto(char);

    void setEstadoInicial(std::string nombreEstadoInicial);

//    ~Automata(); //virtual?
};


#endif //AFD_AUTOMATA_H
