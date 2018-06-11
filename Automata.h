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
    const Estado *estadoInicial; // int * const ptr;         Declares a const pointer to int type. You're not allowed to modify ptr, but the data pointed

    unsigned int nroElementosAlfabeto;
    unsigned int cantActualElementosAlfabeto;
    char *alfabeto;

    // banderas del automata
    bool automataListo;       // true cuando se puede hacer transiciones
    bool tieneEstadoInicial;
    bool tieneEstadoSalida;
    bool tieneEstadosDefinidos; //true cuando el usuario tiene tantos estados como ha establecido en el constructor
    bool tieneEntradasDefinidas; //true cuando el usuario tiene tantos simbolos de entrada como declarados
    bool tieneFDeterminada;           // true si la funcion de transición está definida o usada por primera vez

    virtual void setAutomataListo() =0;

    virtual std::string getExpresionFormal() =0;

    //metodos auxiliares
    unsigned int getEstadoIndex(const std::string &nombreEstado);

    unsigned int getAlfabetoIndex(char elementoAlfabeto);

//    bool nombreEstadoDisponible(std::string n);
//    bool simboloEntradaDisponible(char c);

public:
    Automata(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    virtual void transicion(char) =0;
    // como hacer para que las funciones derivadas deban implementarla con distintos parametros;

    unsigned int getNroEstados() const;

    void setEstado(const std::string &nombreEstado, bool estadoSalida);

protected:
    void setEstadoActual(const std::string &nombreEstado);

public:
    std::string getNombreEstadoActual() const;

    bool getSituacionEstadoActual() const;

    unsigned int getNroElementosAlfabeto() const;

    void setAlfabeto(char);

    void setEstadoInicial(std::string nombreEstadoInicial);

    std::string getNombreEstadoInicial();

//    ~Automata(); //virtual?
};


#endif //AFD_AUTOMATA_H
