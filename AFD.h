//
// Created by FrancoBobadilla on 15/4/2018.
//

#ifndef AFD_AFD_H
#define AFD_AFD_H

#include "Estado.h"

class AFD {
private:
    int nE;
    Estado *est;
    int nEAlf;
    char *alf;
    Estado estAct;
    //char entAct;
    Estado **f;
public:
    AFD(int, int);

    int transicion(char);
};

#endif //AFD_AFD_H
