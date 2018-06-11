#include <include/gtest/gtest.h>

#include "../../Automata.h"
#include "../../Automata.cpp"
#include "../../AFD.h"
#include "../../AFD.cpp"
#include "../../APila.h"
#include "../../APila.cpp"
#include "../../MTuring.h"
#include "../../MTuring.cpp"

#include "../../Estado.h"
#include "../../Estado.cpp"

#include "../../Data_Structures/Celda.h"
#include "../../Data_Structures/Cinta.h"
#include "../../Data_Structures/Node.h"
#include "../../Data_Structures/Stack.h"

AFD *F;
APila *P;
MTuring *M;

TEST(test_prueba, test_trivialmente_verdadero) {
    EXPECT_EQ(1, 1);
}

// hacer un automata finito determinista que de salida si la cantidad de 1 en una cadena es impar
TEST(test_prueba, AFD_1) {
    F = new AFD(2, 2);
}

TEST(test_prueba, AFD_Exceptions) {
    F = new AFD(2, 3);
    ASSERT_ANY_THROW(F->transicion(2));
    ASSERT_ANY_THROW(F->getExpresionFormal());
    ASSERT_ANY_THROW(F->getNombreEstadoInicial());
    ASSERT_ANY_THROW(F->getNombreEstadoActual());
    ASSERT_ANY_THROW(F->getSituacionEstadoActual());
    ASSERT_ANY_THROW(F->setEstadoInicial("q1"));

    ASSERT_EQ(F->getNroEstados(), 2);
    ASSERT_EQ(F->getNroElementosAlfabeto(), 3);
    // metodos para ver la cantidad actual?

    ASSERT_NO_THROW(F->setEstado("q1", false));
    ASSERT_ANY_THROW(F->setEstado("q1", true));

    ASSERT_NO_THROW(F->setEstadoInicial("q1"));
    ASSERT_EQ(F->getNombreEstadoInicial(), "q1");
    ASSERT_EQ(F->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(F->getSituacionEstadoActual());

    ASSERT_ANY_THROW(F->setEstadoInicial("q1"));

    ASSERT_NO_THROW(F->setAlfabeto('a'));
    ASSERT_ANY_THROW(F->setAlfabeto('a'));

    ASSERT_NO_THROW(F->setF("q1", 'a', "q1"));
    ASSERT_ANY_THROW(F->setF("q1", 'a', "q1"));
    ASSERT_ANY_THROW(F->transicion(2));
    ASSERT_ANY_THROW(F->getExpresionFormal());

    ASSERT_NO_THROW(F->setEstado("q2", true));
    ASSERT_ANY_THROW(F->setEstado("q2", false));
    ASSERT_ANY_THROW(F->setEstado("q3", false));

    ASSERT_ANY_THROW(F->setF("q1", 'a', "q2"));
    ASSERT_ANY_THROW(F->setF("q1", 'a', "q1"));

    ASSERT_NO_THROW(F->setAlfabeto('b'));
    ASSERT_NO_THROW(F->setF("q1", 'b', "q2"));

    ASSERT_NO_THROW(F->setAlfabeto('c'));
    ASSERT_ANY_THROW(F->setAlfabeto('d'));

    ASSERT_ANY_THROW(F->transicion('c'));

    ASSERT_NO_THROW(F->setF("q1", 'c', "q1"));
    ASSERT_NO_THROW(F->setF("q2", 'b', "q1"));
    ASSERT_NO_THROW(F->setF("q2", 'a', "q2"));
    ASSERT_NO_THROW(F->setF("q2", 'c', "q2"));

    EXPECT_EQ(F->getExpresionFormal(), "");

    //afd que da salida con b impares

    ASSERT_ANY_THROW(F->setF("q2", 'd', "q2"));
    ASSERT_ANY_THROW(F->setF("q2", 'c', "q2"));


    ASSERT_NO_THROW(F->transicion('b'));
    ASSERT_EQ(F->getNombreEstadoActual(), "q2");
    ASSERT_TRUE(F->getSituacionEstadoActual());

    ASSERT_NO_THROW(F->transicion('a'));
    ASSERT_EQ(F->getNombreEstadoActual(), "q2");
    ASSERT_TRUE(F->getSituacionEstadoActual());
    ASSERT_NO_THROW(F->transicion('c'));
    ASSERT_EQ(F->getNombreEstadoActual(), "q2");
    ASSERT_TRUE(F->getSituacionEstadoActual());

    ASSERT_EQ(F->getNombreEstadoInicial(), "q1");

    ASSERT_ANY_THROW(F->transicion('d'));

    ASSERT_NO_THROW(F->transicion('b'));
    ASSERT_EQ(F->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(F->getSituacionEstadoActual());
    ASSERT_NO_THROW(F->transicion('c'));
    ASSERT_EQ(F->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(F->getSituacionEstadoActual());

    ASSERT_ANY_THROW(F->setEstadoInicial("q2"));
    ASSERT_ANY_THROW(F->setEstado("q2", true));
    ASSERT_ANY_THROW(F->setAlfabeto('c'));

}


//TEST(test_prueba, MTuring_ParOImpar) {
//// escribe P en la cinta si hay una cantidad par de 0
//    // escribe I si la cantidade de 0 es impar
//
//    M = new MTuring(1, 2, 4, '/');
//    ASSERT_EQ(1, M->getNroEstados());
//    ASSERT_EQ(2, M->getNroElementosAlfabeto());
////    ASSERT_EQ(4, M->getNroElementosAlfabetoCinta());
////    ASSERT_EQ('/', M.getBlanco());
//    ASSERT_EQ(M->getLecturaCabezal(), '/');
//}
//
//
//TEST(test_prueba, Automata_general) {
//    F = new AFD(2, 2);
//    ASSERT_EQ(F->getNroEstados(), 2);
//    ASSERT_EQ(F->getNroElementosAlfabeto(), 2);
//
//}