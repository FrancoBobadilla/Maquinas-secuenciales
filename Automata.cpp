//
// Created by nelon on 5/4/2018.
//

#include "Automata.h"

Automata::Automata(unsigned int cantEstados, unsigned int tamAlfabeto) {
    if (0 >= cantEstados || 0 >= tamAlfabeto) //si la cantidad de estados es uInt, ¿no es siempre >= 0?
        throw 0;
    this->nroEstados = cantEstados;
    this->cantActualEstados = 0;
    this->estados = new Estado[cantEstados];
    this->estadoActual = nullptr;
    this->estadoInicial = nullptr;

    this->nroElementosAlfabeto = tamAlfabeto;
    this->cantActualElementosAlfabeto = 0;
    this->alfabeto = new char[tamAlfabeto];     //podria considerarse que sean strings

    //seteo de banderas
    this->automataListo = false;
    this->tieneEstadoInicial = false;
    this->tieneEstadoSalida = false;
    this->tieneEstadosDefinidos = false;
    this->tieneEntradasDefinidas = false;
    this->tieneFDeterminada = false;

    this->cadenaAnalizar = "";
    this->tieneCadenaAnalizar = false;
    this->automataApagado = false;
}

void Automata::setEstado(const std::string &nombreEstado, bool estadoSalida) {
    if (this->tieneEstadosDefinidos)
        throw -1;           // ya tiene todos los estados ocupados

    unsigned int eIndex;

    try {
        eIndex = this->getEstadoIndex(nombreEstado);
    } catch (int exc) {
        this->estados[this->cantActualEstados].nombre = nombreEstado;
        this->estados[this->cantActualEstados].situacion = estadoSalida;
        this->cantActualEstados++;

        if (estadoSalida)
            this->tieneEstadoSalida = true;

        if (this->cantActualEstados == this->nroEstados) {
            this->tieneEstadosDefinidos = true;
            this->setAutomataListo();
        }
        return;
    }
    // conceptualmente esta mal: esta tomando como excepcion algo que esta bien
    throw -2;
}

unsigned int Automata::getNroEstados() const {
    return this->nroEstados;
}

void Automata::setEstadoActual(const std::string &nombreEstado) {
    this->estadoActual = &this->estados[getEstadoIndex(nombreEstado)];
}

std::string Automata::getNombreEstadoActual() const {
    if (!this->tieneEstadoInicial)
        throw -85;
    return this->estadoActual->nombre;
}

bool Automata::getSituacionEstadoActual() const {
    if (!this->tieneEstadoInicial)
        throw -85;
    return this->estadoActual->situacion;
}

/*
   * Este bloque es para definir el estado inicial del automata,
   * que pertenece a est[]
   */
void Automata::setEstadoInicial(std::string nombreEstadoInicial) {
    if (this->tieneEstadoInicial)
        throw -1;

    try {
        this->estadoInicial = &this->estados[getEstadoIndex(nombreEstadoInicial)];
    } catch (int exc) {
        throw exc;
    }
    this->tieneEstadoInicial = true;
    this->setAutomataListo();

    this->setEstadoActual(nombreEstadoInicial);
}

/*
     * El siguiente bloque es para cargar el alfabeto de entrada de tamaño nEAlf en alf[],
     * y tampoco se admiten entradas repetidas
     *
     */
void Automata::setAlfabeto(char c) {
    if (this->tieneEntradasDefinidas)
        throw -1;       // ya está lleno

    unsigned int cIndex;

    try {
        cIndex = this->getAlfabetoIndex(c);
    } catch (int exc) {
        this->alfabeto[this->cantActualElementosAlfabeto] = c;
        this->cantActualElementosAlfabeto++;

        if (this->nroElementosAlfabeto == this->cantActualElementosAlfabeto) {
            this->tieneEntradasDefinidas = true;
            this->setAutomataListo();
        }
        return;
    }
    // conceptualmente esta mal: esta tomando como excepcion algo que esta bien
    throw -2;
}
// ERROR 1 lleno
// ERROR 2 Repetido

unsigned int Automata::getNroElementosAlfabeto() const {
    return this->nroElementosAlfabeto;
}

std::string Automata::getNombreEstadoInicial() {
    if (!this->tieneEstadoInicial)
        throw -85;
    return this->estadoInicial->nombre;
}

unsigned int Automata::getEstadoIndex(const std::string &e) {
    for (unsigned int i = 0; i < this->cantActualEstados; ++i) {
        if (e == this->estados[i].nombre)
            return i;
    }
    throw -1;
}

unsigned int Automata::getAlfabetoIndex(char c) {
    for (unsigned int i = 0; i < this->cantActualElementosAlfabeto; ++i) {
        if (c == this->alfabeto[i])
            return i;
    }
    throw -1;
}

void Automata::setCadenaAnalizar(std::string s) {
    if (this->tieneCadenaAnalizar)
        throw -2;
    if ("" == s)
        throw -5;

    unsigned int i = 0;
    while ('\0' != s[i]) {
        try {
            this->getAlfabetoIndex(s[i]); // si existe la entreada
        } catch (int exc) {
            if (-1 == exc) {
                this->cadenaAnalizar = "";
                throw -21;   //No pertenece al alfabeto de entrada
            }
        }
        //cambiar despues por funcion existe();

        this->cadenaAnalizar += s[i];
        i++;
    }
    this->tieneCadenaAnalizar = true;
    this->setAutomataListo();
}

bool Automata::isAutomataApagado() {
    return this->automataApagado;
}

std::string Automata::getExpresionFormal() {
    if (!this->expresionFormalLista())
        throw -0;
    char i;
    std::string r = "";
    r += this->tipoAutomata() + " = ( { ";

    for (i = 0; i < this->nroElementosAlfabeto - 1; i++) {
        r += this->alfabeto[i];
        r += ", ";
    }
    r += this->alfabeto[i];
    r += " }, ";

    r += this->expresionEspecifica();

    r += this->estadoInicial->nombre + ", { ";

    std::string estadosfinales = "";

    for (i = 0; i < this->getNroEstados() - 1; ++i) {
        r += this->estados[i].nombre + ", ";
        if (this->estados[i].situacion)
            estadosfinales += this->estados[i].nombre + ", ";
    }
    r += this->estados[i].nombre + " },";
    if (this->estados[i].situacion)
        estadosfinales += this->estados[i].nombre;
    // muestra una coma de mas;

    r += " { " + estadosfinales + "}, f )";
    return r;
}