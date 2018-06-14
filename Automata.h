//
// Created by nelon on 5/4/2018.
//

#ifndef AFD_AUTOMATA_H
#define AFD_AUTOMATA_H

#include<iostream>

struct Estado {
    std::string nombre;
    bool situacion;
};

class Automata {
protected:
    // Atributos para los estados
    unsigned int nroEstados;
    unsigned int cantActualEstados;
    Estado *estados;
    const Estado *estadoActual;
    const Estado *estadoInicial;

    // Atributos para el alfabeto de entrada
    unsigned int nroElementosAlfabeto;
    unsigned int cantActualElementosAlfabeto;
    char *alfabeto;

    // Atributos para la cadena de entrada a analizar por el automata
    std::string cadenaAnalizar;

    // banderas del automata
    bool automataListo;       // true cuando se puede hacer transiciones
    bool tieneEstadoInicial;
    bool tieneEstadoSalida;
    bool tieneEstadosDefinidos; //true cuando el usuario tiene tantos estados como ha establecido en el constructor
    bool tieneEntradasDefinidas; //true cuando el usuario tiene tantos simbolos de entrada como declarados
    bool tieneFDeterminada;           // true si la funcion de transición está definida o usada por primera vez
    bool tieneCadenaAnalizar;   // true si el usuario a ingresado completamente la cadena a analizar
    bool automataApagado;   // true si ya termino de andar


    void setEstadoActual(const std::string &nombreEstado);

    virtual void setAutomataListo() =0;


    //metodos auxiliares
    unsigned int getEstadoIndex(const std::string &nombreEstado);

    unsigned int getAlfabetoIndex(char elementoAlfabeto);

    bool existsIn(const std::string &, const Estado *, unsigned int);

    bool existsIn(char, const char *, unsigned int);

//    bool nombreEstadoDisponible(std::string n);
//    bool simboloEntradaDisponible(char c);

public:
    Automata(unsigned int cantidadEstados, unsigned int tamanoAlfabeto);

    virtual void transicion() =0;

    std::string getExpresionFormal();

    virtual void setCadenaAnalizar(std::string);

    // metodos de estado
    void setEstado(const std::string &nombreEstado, bool estadoSalida);

    void setEstadoInicial(std::string nombreEstadoInicial);

    std::string getNombreEstadoInicial();

    unsigned int getNroEstados() const;

    std::string getNombreEstadoActual() const;

    bool getSituacionEstadoActual() const;


    //metodos de alfabeto de simbolos de entrada
    void setAlfabeto(char);

    unsigned int getNroElementosAlfabeto() const;


    bool isAutomataApagado();

    // metodos para expresion formal
    virtual std::string tipoAutomata() =0;

    virtual bool expresionFormalLista() =0;

    virtual std::string expresionEspecifica() =0;

    Automata(const Automata&);

    virtual~Automata(); //virtual?
};


#endif //AFD_AUTOMATA_H
