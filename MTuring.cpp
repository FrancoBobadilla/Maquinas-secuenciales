//
// Created by FrancoBobadilla on 31/5/2018.
//

#include "MTuring.h"

MTuring::MTuring(unsigned int cantidadEstados, unsigned int tamanoAlfabeto, unsigned int tamanoAlfabetoCinta,
                 char blanco)
        : Automata(cantidadEstados, tamanoAlfabeto) {
    if (0 >= tamanoAlfabetoCinta)
        throw 0;

    this->nroElementosAlfabetoCinta = tamanoAlfabetoCinta + 1;  //para el blanco
    this->cantActualElementosAlfabetoCinta = 0;
    this->alfabetoCinta = new char[this->nroElementosAlfabetoCinta];

    //seteo de banderas
    this->isCabezalListo = false;
    this->tieneSimbolosCintaDefinidos = false;

    this->cinta = new Cinta<char>(blanco);
    // el blanco cuenta como simbolo del alfabeto de cinta?
    this->setAlfabetoCinta(blanco);

    // f [ESTADO ACTUAL] [ENTRADA DESDE CINTA]
    this->f = new SalidaFuncMaqTuring **[this->nroEstados];
    for (int i = 0; i < this->nroEstados; ++i) {
        this->f[i] = new SalidaFuncMaqTuring *[this->nroElementosAlfabetoCinta];       // mas el blanco
        for (int j = 0; j < this->nroElementosAlfabetoCinta; ++j) {
            this->f[i][j] = nullptr;
        }
    }
}

void MTuring::setF(std::string nombreEstadoSalida, char entradaCinta, std::string nombreEstadoDestino,
                   char direccion, char escritura) {
    unsigned int ESalidaIndex, entradaCintaIndex, EDestinoIndex, escrituraIndex;

    if (this->tieneFDeterminada)
        throw -23;

    try {
        ESalidaIndex = this->getEstadoIndex(nombreEstadoSalida);
    } catch (int exc) {
        if (-1 == exc)
            throw -11;
    }
    try {
        EDestinoIndex = this->getEstadoIndex(nombreEstadoDestino);
    } catch (int exc) {
        if (-1 == exc) {
            throw -12;
        }
    }
    try {
        entradaCintaIndex = getAlfabetoCintaIndex(entradaCinta);
    } catch (int exc) {
        if (-1 == exc)
            throw -18;
    }
    try {
        escrituraIndex = getAlfabetoCintaIndex(escritura);
    } catch (int exc) {
        if (-1 == exc)
            throw -19;
    }

    //(p: mantener, i:izquierda, d:derecha)
    // direccion no valida
    if ('p' != tolower(direccion) && 'i' != tolower(direccion) && 'd' != tolower(direccion))
        throw -17;

    // controla que sólo se alcanza salida cuando el cabezal para
    if ('p' != tolower(direccion) && this->estados[EDestinoIndex].situacion)
        throw -50;

    // controla que el cabezal puede pararse sólo al alcanzar salida
    if ('p' == tolower(direccion) && !this->estados[EDestinoIndex].situacion)
        throw -51;

    if (nullptr != f[ESalidaIndex][entradaCintaIndex])
        throw -16;

    // tiene que haber una forma prolija de hacerlo
    this->f[ESalidaIndex][entradaCintaIndex] = new SalidaFuncMaqTuring;
    this->f[ESalidaIndex][entradaCintaIndex]->estado.nombre = this->estados[EDestinoIndex].nombre;
    this->f[ESalidaIndex][entradaCintaIndex]->estado.situacion = this->estados[EDestinoIndex].situacion;
    this->f[ESalidaIndex][entradaCintaIndex]->direccion = (char) tolower(direccion);
    this->f[ESalidaIndex][entradaCintaIndex]->escritura = this->alfabetoCinta[escrituraIndex];
}

void MTuring::setAlfabetoCinta(char c) {
    if (this->tieneSimbolosCintaDefinidos)
        throw -1;          //ya esta lleno

    if (this->existsIn(c, this->alfabetoCinta, this->cantActualElementosAlfabetoCinta))
        throw -2;

    this->alfabetoCinta[this->cantActualElementosAlfabetoCinta] = c;
    this->cantActualElementosAlfabetoCinta++;
    if (this->cantActualElementosAlfabetoCinta == this->nroElementosAlfabetoCinta) {
        this->tieneSimbolosCintaDefinidos = true;
        this->setAutomataListo();
    }

}

void MTuring::setCadenaAnalizar(std::string s) {
    if (this->tieneCadenaAnalizar)
        throw -2;
    if ("" == s)
        throw -5;

    unsigned int i = 0;
    while ('\0' != s[i]) {
        if (!this->existsIn(s[i], this->alfabeto, this->cantActualElementosAlfabeto)) {
            this->cadenaAnalizar = "";
            throw -21;   //No pertenece al alfabeto de entrada
        }
        this->cadenaAnalizar += s[i];
        i++;
    }
    this->escribirCinta(this->cadenaAnalizar);
    this->tieneCadenaAnalizar = true;
    this->setAutomataListo();
}

inline void MTuring::escribirCinta(std::string s) {
    unsigned int i = 0;
    while ('\0' != s[i]) {
        this->cinta->desplazarDerecha();
        this->cinta->escribir(s[i]);
        i++;
    }
    this->cinta->desplazarDerecha();
}

std::string MTuring::getCopiaCinta() {
    return this->cinta->devolverCopiaCinta();
}

void MTuring::transicion() {
    if (this->automataApagado)
        throw -1;
    if (!this->tieneCadenaAnalizar)
        throw -2;       // no se puede hacer tranciciones hasta que la cinta no este lista
    if (!this->isCabezalListo)
        throw -3;

    char lectura = this->cinta->leer();
    SalidaFuncMaqTuring *salidaF;
    try {
        salidaF = this->f[this->getEstadoIndex(this->estadoActual->nombre)][this->getAlfabetoCintaIndex(lectura)];
    } catch (int exc) {
        if (-1 == exc)
            throw -21;
        // se da en caso de que el alfabeto de entrada no esté comprendido en el de cinta
    }

    if (nullptr == salidaF) {
        Estado *tmpEstado = new Estado();
        tmpEstado->nombre = "ESTADO DE ERROR";
        tmpEstado->situacion = false;
        this->estadoActual = tmpEstado;
        this->automataApagado = true;
        //define automata como no usable
    } else {
        this->estadoActual = &salidaF->estado;
        if (this->estadoActual->situacion)
            this->automataApagado = true;

        this->cinta->escribir(salidaF->escritura);

        //en caso de que se reemplace un blanco por otro simbolo
        //el cabezal se mueve hacia la izquierda y la derecha
        //colocando un blanco en el lado correspondiente
        if (lectura == this->cinta->getBlanco()
            && salidaF->escritura != this->cinta->getBlanco()) {
            this->cinta->desplazarDerecha();
            this->cinta->desplazarIzquierda();
            this->cinta->desplazarIzquierda();
            this->cinta->desplazarDerecha();
        }

        if ('d' == salidaF->direccion) {
            this->cinta->desplazarDerecha();
        } else {
            if ('i' == salidaF->direccion)
                this->cinta->desplazarIzquierda();
        }

        if (!this->tieneFDeterminada) {
            this->tieneFDeterminada = true;
            this->setAutomataListo();
        }
    }
}

unsigned int MTuring::getAlfabetoCintaIndex(const char &s) {
    for (unsigned int i = 0; i < this->cantActualElementosAlfabetoCinta; ++i) {
        if (s == this->alfabetoCinta[i])
            return i;
    }
    throw -1;
}

char MTuring::getLecturaCabezal() {
    return this->cinta->leer();
}

void MTuring::ponerCabezal(unsigned int pos) {
    if (!this->tieneCadenaAnalizar)
        throw -1;   // solo se puede situar el cabezal cuando la cinta está cargada
    if (this->isCabezalListo)
        throw -2;   // solo se puede poner el cabezal una vez
    if (this->cinta->getTamano() <= pos)
        throw -3;   // la cinta es mas chica

    //el cabezal está sobre el último blanco
    //el cabezal está en la posición tamano-1

    unsigned int i = this->cinta->getTamano() - 1 - pos;
    while (0 != i) {
        this->cinta->desplazarIzquierda();
        i--;
    }
    this->isCabezalListo = true;
    this->setAutomataListo();
}

unsigned int MTuring::getNroElementosAlfabetoCinta() {
    return this->nroElementosAlfabetoCinta;
}

bool MTuring::expresionFormalLista() {
    return !(!this->tieneEstadoInicial ||
             !this->tieneEstadoSalida ||
             !this->tieneEstadosDefinidos ||
             !this->tieneEntradasDefinidas ||
             !this->tieneSimbolosCintaDefinidos);
}

void MTuring::setAutomataListo() {
    this->automataListo = this->tieneEstadoInicial &&
                          this->tieneEstadoSalida &&
                          this->tieneEstadosDefinidos &&
                          this->tieneEntradasDefinidas &&
                          this->tieneFDeterminada &&
                          this->tieneSimbolosCintaDefinidos &&
                          this->tieneCadenaAnalizar &&
                          this->isCabezalListo;
}

std::string MTuring::tipoAutomata() {
    return "MT";
}

std::string MTuring::expresionEspecifica() {
    std::string r = "{ ";
    char i;
    for (i = 0; i < this->nroElementosAlfabetoCinta - 1; i++) {
        r += this->alfabetoCinta[i];
        r += ", ";
    }
    r += this->alfabetoCinta[i];
    r += " }, ";
    r += this->cinta->getBlanco();
    r += ", ";

    return r;
}