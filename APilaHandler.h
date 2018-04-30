//
// Created by FrancoBobadilla on 30/4/2018.
//

#ifndef AFD_APILAHANDLER_H
#define AFD_APILAHANDLER_H

#include "APila.h"
#include "Data_Structures/Stack.h"

class APilaHandler {
private:
    Stack<APila> Principal;
    Stack<APila> Auxiliar;
public:
    APilaHandler(int, int, int);
    void transicion(char);
};

#endif //AFD_APILAHANDLER_H
