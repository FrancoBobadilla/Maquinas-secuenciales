//
// Created by FrancoBobadilla on 31/5/2018.
//

#ifndef AFD_MTURING_H
#define AFD_MTURING_H

#include "Data_Structures/Cinta.h"
#include "Automata.h"

struct SalidaFuncMaqTuring {
    Estado estado;      //estado al cual se llega
    char direccion;     //direccion a la que se mueve el cabezal (p: mantener, i:izquierda, d:derecha)
    char escritura;     //simbolo que escribe el cabezal en la cinta
};

class MTuring : public Automata {
private:
    SalidaFuncMaqTuring ****f;

    Cinta<char> cinta;

    unsigned int nroElementosAlfabetoCinta;
    unsigned int cantActualElementosAlfabetoCinta;
    char *alfabetoCinta;

    unsigned int getAlfabetoCintaIndex(const char &simboloEntradaCinta);

public:
    MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta);

    virtual void transicion(char);

    void setF(std::string nombreEstadoSalida, char entrada, char valorCinta, std::string nombreEstadoDestino,
              char direccion, char escritura);

    void setAlfabetoCinta(char);

    char getLecturaCabezal();
};

#endif //AFD_MTURING_H
