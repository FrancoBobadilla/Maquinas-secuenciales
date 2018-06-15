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

    // atributos del alfabeto de cinta
    Cinta<char> *cinta;
    unsigned int nroElementosAlfabetoCinta;
    unsigned int cantActualElementosAlfabetoCinta;
    char *alfabetoCinta;

    //banderas
    bool isCabezalListo;
    bool tieneSimbolosCintaDefinidos;

    //metodos auxiliares
    unsigned int getAlfabetoCintaIndex(const char &simboloEntradaCinta);

    inline void escribirCinta(std::string);

    void setAutomataListo() override;

public:
    MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta, char blanco);

    void setF(std::string nombreEstadoSalida, char entradaCinta, std::string nombreEstadoDestino,
              char direccion, char escritura);

    void transicion() override;

    void reiniciarAutomata() override;

    void setCadenaAnalizar(std::string) override;

    // métodos para simbolos del alfabeto de entrada de cinta
    void setAlfabetoCinta(char);

    unsigned int getNroElementosAlfabetoCinta();

    std::string getCopiaCinta();

    char getLecturaCabezal();

    void ponerCabezal(unsigned int);

    std::string tipoAutomata() override;

    std::string expresionEspecifica() override;

    MTuring(const MTuring &);

    ~MTuring();
};

#endif //AFD_MTURING_H
