//
// Created by nelon on 5/4/2018.
//

#include "Automata.h"

Automata::Automata(unsigned int cantEstados, unsigned int tamAlfabeto) {
    this->nroEstados = cantEstados;
    this->cantActualEstados = 0;
    this->estados = new Estado[cantEstados];
//    this->estadoActual = nullptr;   // esto esta mal

    this->nroElementosAlfabeto = tamAlfabeto;
    this->cantActualElementosAlfabeto = 0;
    this->alfabeto = new char[tamAlfabeto];     //podria considerarse que sean strings

    this->isCargado = false;
}

unsigned int Automata::getNroEstados() const {
    return this->nroEstados;
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

std::string Automata::getEstadoActual() const {
    return this->estadoActual.nombre;
}

void Automata::setEstadoActual(std::string nombreEstado) {
    this->estadoActual = this->estados[getEstadoIndex(nombreEstado)];
}

void Automata::setEstadoInicial(std::string nombreEstadoInicial) {
    //deberia chequear que no se haya ingresado un estado inicial previamente;
    this->setEstadoActual(nombreEstadoInicial);
}

unsigned int Automata::getNroElementosAlfabeto() const {
    return this->nroElementosAlfabeto;
}

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