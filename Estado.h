//
// Created by FrancoBobadilla on 15/4/2018.
//

#ifndef AFD_ESTADO_H
#define AFD_ESTADO_H


#include <iostream>

class Estado {
public:
    std::string nombre;
    bool situacion;

    void operator=(const Estado &);

    Estado() = default;
};

#endif //AFD_ESTADO_H
