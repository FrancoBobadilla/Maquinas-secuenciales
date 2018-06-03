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
    SalidaFuncMaqTuring ***f;

    Cinta<char> *cinta;

    unsigned int nroElementosAlfabetoCinta;
    unsigned int cantActualElementosAlfabetoCinta;
    char *alfabetoCinta;

    unsigned int getAlfabetoCintaIndex(const char &simboloEntradaCinta);

    bool isCintaLista;

    bool isCabezalListo;    // solo se puede ubicar el cabezal una vez

    bool maquinaParada;     // una vez el cabezal se ha detenido, la maquina no trabaja más

    virtual void transicion(char);

    //controlar en todas las maquinas que se hayan cargado todas las entradas y estados ...

public:
    MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta, char blanco);

    void setF(std::string nombreEstadoSalida, char entradaCinta, std::string nombreEstadoDestino,
              char direccion, char escritura);

    void setAlfabetoCinta(char);    //graba el alfabeto aceptado por la cinta

    char getLecturaCabezal();

    void escribirSimboloEnCinta(char c);    //escribe uno a uno los elementos de la cinta

    void setCintaLista();

    void transicion();

    bool isMaquinaParada();

    void ponerCabezal(unsigned int);

    // ver cinta?
};

#endif //AFD_MTURING_H
