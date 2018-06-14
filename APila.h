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

    // atributos de alfabeto de pila
    Stack<char> *pila;
    unsigned int nroElementosAlfabetoPila;
    unsigned int cantActualElementosAlfabetoPila;
    char *alfabetoPila;
    char finDePila;

    //banderas
    bool tieneSimbolosPilaDefinidos;

    //métodos auxiliares
    unsigned int getAlfabetoPilaIndex(const char &simboloEntradaPila);

    Estado *buscarEstadoFinal();

    void setAutomataListo() override;

    void apagarAutomata();

public:
    APila(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoPila,
          char finDePila);

    void setF(std::string nombreEstadoSalida, char entrada, char valorPila, std::string nombreEstadoDestino,
              bool conservarTope, char apilamiento);

    void transicion() override;

    void reiniciarAutomata() override;

    // metodos para simbolos del alfabeto de entrade de pila
    void setAlfabetoPila(char);

    unsigned int getNroElementosAlfabetoPila();

    char getTopeDePila();

    bool expresionFormalLista() override;

    std::string tipoAutomata() override;

    std::string expresionEspecifica() override;

    APila(const APila&);

    ~APila();
};


#endif //AFD_APILA_H