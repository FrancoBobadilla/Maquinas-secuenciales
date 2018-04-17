//
// Created by FrancoBobadilla on 15/4/2018.
//

#include "Estado.h"

void Estado::operator=(const Estado &est) {
    situacion = est.situacion;
    nombre = est.nombre;
}