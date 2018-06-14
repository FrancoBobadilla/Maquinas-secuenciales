//
// Created by FrancoBobadilla on 15/4/2018.
//

#ifndef AFD_AFD_H
#define AFD_AFD_H

#include "Automata.h"

class AFD : public Automata {
private:
    Estado ***f;        // para poder ser nullptr

    void setAutomataListo() override;

    bool isReadyF();

public:
    AFD(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    void setF(std::string nombreEstadoSalida, char entrada, std::string nombreEstadoDestino);

    void transicion() override;

    std::string getExpresionFormal() override;
};

#endif //AFD_AFD_H