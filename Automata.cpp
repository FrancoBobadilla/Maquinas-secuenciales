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

    this->nroElementosAlfabeto = tamAlfabeto;
    this->cantActualElementosAlfabeto = 0;
    this->alfabeto = new char[tamAlfabeto];     //podria considerarse que sean strings
}

void Automata::setEstado(Estado e) {
    if (this->cantActualEstados >= this->nroEstados)
        throw -1;           // ya está lleno

    unsigned int eIndex;

    try {
        eIndex = this->getEstadoIndex(e.nombre);
    } catch (int exc) {
        this->estados[this->cantActualEstados] = e;
        this->cantActualEstados++;
        return;
    }
    // conceptualmente esta mal: esta tomando como excepcion algo que esta bien
    throw -2;
}

unsigned int Automata::getNroEstados() const {
    return this->nroEstados;
}

void Automata::setEstadoActual(std::string nombreEstado) {
    *this->estadoActual = this->estados[getEstadoIndex(nombreEstado)];
}

std::string Automata::getNombreEstadoActual() const {
    return this->estadoActual->nombre;
}

bool Automata::getSituacionEstadoActual() const {
    return this->estadoActual->situacion;
}

/*
   * Este bloque es para definir el estado inicial del automata,
   * que pertenece a est[]
   */
void Automata::setEstadoInicial(std::string nombreEstadoInicial) {
    if (nullptr != estadoActual)
        throw -1;       //ya está lleno
    this->setEstadoActual(nombreEstadoInicial);
}

/*
     * El siguiente bloque es para cargar el alfabeto de entrada de tamaño nEAlf en alf[],
     * y tampoco se admiten entradas repetidas
     *
     */

void Automata::setAlfabeto(char c) {
    if (this->cantActualElementosAlfabeto >= this->nroElementosAlfabeto)
        throw -1;       // ya está lleno

    unsigned int cIndex;

    try {
        cIndex = this->getAlfabetoIndex(c);
    } catch (int exc) {
        this->alfabeto[this->cantActualElementosAlfabeto] = c;
        this->cantActualElementosAlfabeto++;
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

unsigned int Automata::getEstadoIndex(std::string e) {
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