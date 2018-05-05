#include <iostream>
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

    this->f[ESalida][entIndex] = new Estado;
    this->f[ESalida][entIndex]->nombre = this->estados[EDestino].nombre;
    this->f[ESalida][entIndex]->situacion = this->estados[EDestino].situacion;
}

Estado AFD::transicion(char entrada) {
    if (!this->isReadyF())
        throw -8;       // F no esta toda cargada
    /*
     * IMPORTANTE
     *
     * deberia haber dato miembro
     *          bool FReady
     * para evitar recorrer toda la matriz f con cada transicion
     *
     * */

    unsigned int entradaIndex;
    try {
        entradaIndex = this->getAlfabetoIndex(entrada);
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
    }

    estadoActual.nombre = this->f[this->getEstadoIndex(estadoActual.nombre)][entradaIndex]->nombre;
    estadoActual.situacion = this->f[this->getEstadoIndex(estadoActual.nombre)][entradaIndex]->situacion;
    // se deberia conservar el index del estado acual para que así
    // f[IndexActual]

    // o bien estado actual deberia ser un puntero, que apunta al arreglo de estados en la posicion del actual

    return estadoActual;
}

bool AFD::isReadyF() {
    for (int i = 0; i < this->nroEstados; ++i)
        for (int j = 0; j < this->nroElementosAlfabeto; ++j)
            if (nullptr == f[i][j])
                return false;
    return true;
}