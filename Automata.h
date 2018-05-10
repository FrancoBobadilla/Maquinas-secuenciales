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
    const Estado *estadoActual;

    /* const int * ptr;         Declares a pointer to const int type. You may modify ptr, but not its data
     * int * const ptr;         Declares a const pointer to int type. You're not allowed to modify ptr, but the data pointed
     * */

    unsigned int nroElementosAlfabeto;
    unsigned int cantActualElementosAlfabeto;
    char *alfabeto;

    //metodos auxiliares
    unsigned int getEstadoIndex(const std::string &nombreEstado);

    unsigned int getAlfabetoIndex(char elementoAlfabeto);

public:
    Automata(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    virtual void transicion(char) =0;
    // como hacer para que las funciones derivadas deban implementarla con distintos parametros;

    unsigned int getNroEstados() const;

    void setEstado(Estado);

protected:
    void setEstadoActual(const std::string &nombreEstado);

public:
    std::string getNombreEstadoActual() const;

    bool getSituacionEstadoActual() const;

    unsigned int getNroElementosAlfabeto() const;

    void setAlfabeto(char);

    void setEstadoInicial(std::string nombreEstadoInicial);

//    ~Automata(); //virtual?
};


#endif //AFD_AUTOMATA_H
