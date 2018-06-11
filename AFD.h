//
// Created by FrancoBobadilla on 15/4/2018.
//

#ifndef AFD_AFD_H
#define AFD_AFD_H

#include "Automata.h"

class AFD : public Automata {
private:
    Estado ***f;        // para poder ser nullptr

    bool isReadyF();

public:
    AFD(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    void setF(std::string nombreEstadoSalida, char entrada, std::string nombreEstadoDestino);

    virtual void transicion(char);

    virtual void setAutomataListo();

    virtual std::string getExpresionFormal();
};


//falta corroborar que haya al menos un estado que sea de salida

#endif //AFD_AFD_H
