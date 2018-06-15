//#include <iostream>
#include "AFD.h"

using namespace std;

AFD::AFD(unsigned int cantEstados, unsigned int tamAlfabeto) : Automata(cantEstados, tamAlfabeto) {
    this->f = new Estado **[cantEstados];
    for (int i = 0; i < cantEstados; ++i) {
        f[i] = new Estado *[tamAlfabeto];
        for (int j = 0; j < tamAlfabeto; ++j)
            f[i][j] = nullptr;
    }
    //primer paramtro representa filas (estados)
    //segundo paramtetro representa columnas (entradas)
}

void AFD::setF(std::string nombreEstadoSalida, char entrada, std::string nombreEstadoDestino) {
    unsigned int ESalida, EDestino, entIndex;

    if (tieneFDeterminada)
        throw -23;              // la funcion de transicion ya fue definida

    try {
        ESalida = this->getEstadoIndex(nombreEstadoSalida);
    } catch (int exc) {
        if (-1 == exc)
            throw -11;
    }
    try {
        EDestino = this->getEstadoIndex(nombreEstadoDestino);
    } catch (int exc) {
        if (-1 == exc)
            throw -12;
    }
    try {
        entIndex = this->getAlfabetoIndex(entrada);
    } catch (int exc) {
        if (-1 == exc)
            throw -13;
    }

    if (nullptr != this->f[ESalida][entIndex])
        throw -14;

    this->f[ESalida][entIndex] = new Estado();
    this->f[ESalida][entIndex]->nombre = this->estados[EDestino].nombre;
    this->f[ESalida][entIndex]->situacion = this->estados[EDestino].situacion;
    // se puede usar sobrecarga asignacion?

    this->tieneFDeterminada = this->isReadyF();
}

void AFD::transicion() {
    if (!this->automataListo || this->automataApagado) // o automata apagado
        throw -8;

    if (this->cadenaAnalizar[1] == '\0') {
        this->automataApagado = true;
    }
    char entrada = this->cadenaAnalizar[0];
    this->cadenaAnalizar = &this->cadenaAnalizar[1];

    estadoActual = this->f[this->getEstadoIndex(estadoActual->nombre)][this->getAlfabetoIndex(entrada)];
    // no puede dar error porque entrada ya fue verificada en setCadenaAnalizar
}

bool AFD::isReadyF() {
    for (int i = 0; i < this->nroEstados; ++i)
        for (int j = 0; j < this->nroElementosAlfabeto; ++j)
            if (nullptr == f[i][j])
                return false;
    this->tieneFDeterminada = true;
    this->setAutomataListo();
    return true;
}

void AFD::setAutomataListo() {
    this->automataListo = this->tieneEstadoInicial &&
                          this->tieneEstadoSalida &&
                          this->tieneEstadosDefinidos &&
                          this->tieneEntradasDefinidas &&
                          this->tieneFDeterminada &&
                          this->tieneCadenaAnalizar;
}

std::string AFD::tipoAutomata() {
    return "AFD";
}

std::string AFD::expresionEspecifica() {
    return "";
}

void AFD::reiniciarAutomata() {
    this->automataListo = false;
    this->automataApagado = false;

    this->cadenaAnalizar = "";
    this->tieneCadenaAnalizar = false;

    this->estadoActual = this->estadoInicial;
}

AFD::AFD(const AFD &x) : Automata(x) {
    this->f = new Estado **[this->nroEstados];
    for (int i = 0; i < this->nroEstados; ++i) {
        this->f[i] = new Estado *[this->nroElementosAlfabeto];
        for (int j = 0; j < this->nroElementosAlfabeto; ++j) {
            if (nullptr == x.f[i][j])
                this->f[i][j] = nullptr;
            else {
                this->f[i][j] = new Estado;
                this->f[i][j]->nombre = x.f[i][j]->nombre;
                this->f[i][j]->situacion = x.f[i][j]->situacion;
            }
        }
    }

    cout << "Saliendo de AFD:constructor por copia\n";
}

AFD::~AFD() {
    for (int i = 0; i < this->nroEstados; ++i) {
        for (int j = 0; j < this->nroElementosAlfabeto; ++j)
            delete f[i][j];
        delete this->f[i];
    }
    delete f;

    cout << "Saliendo de AFD:destructor\n";
}