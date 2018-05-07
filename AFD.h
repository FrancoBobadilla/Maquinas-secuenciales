//
// Created by FrancoBobadilla on 15/4/2018.
//

#ifndef AFD_AFD_H
#define AFD_AFD_H

#include "Automata.h"

class AFD : public Automata {
private:
    Estado ***f;        // para poder ser nullptr
    bool Determinado;
    bool isReadyF();

public:
    AFD(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    void setF(std::string nombreEstadoSalida, char entrada, std::string nombreEstadoDestino);

    virtual Estado transicion(char);
};


//falta corroborar que haya al menos un estado que sea de salida

#endif //AFD_AFD_H
