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
MTuring *T;

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
    ASSERT_ANY_THROW(F->transicion('a'));
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

TEST(test_prueba, APila_Exceptions) {
    P = new APila(4, 2, 1, '#');
    ASSERT_ANY_THROW(P->transicion('2'));
    ASSERT_ANY_THROW(P->getExpresionFormal());
    ASSERT_ANY_THROW(P->getNombreEstadoInicial());
    ASSERT_ANY_THROW(P->getNombreEstadoActual());
    ASSERT_ANY_THROW(P->getSituacionEstadoActual());
    ASSERT_ANY_THROW(P->setEstadoInicial("q1"));

    ASSERT_EQ(P->getNroEstados(), 4);
    ASSERT_EQ(P->getNroElementosAlfabeto(), 2);
//    EXPECT_EQ(P->getNroElementosAlfabetoPila(), 1);

    EXPECT_EQ(P->getTopeDePila(), '#');
    ASSERT_ANY_THROW(P->setAlfabetoPila('#'));

    ASSERT_NO_THROW(P->setEstado("q1", false));
    ASSERT_ANY_THROW(P->setEstado("q1", true));

    ASSERT_NO_THROW(P->setEstadoInicial("q1"));
    ASSERT_EQ(P->getNombreEstadoInicial(), "q1");
    ASSERT_EQ(P->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(P->getSituacionEstadoActual());

    ASSERT_NO_THROW(P->setAlfabeto('a'));
    ASSERT_ANY_THROW(P->setAlfabeto('a'));

    ASSERT_ANY_THROW(P->setEstadoInicial("q1"));
    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q2", true, 'a'));
    ASSERT_ANY_THROW(P->transicion('2'));
//    ASSERT_NO_THROW(P->transicion('a'));
    ASSERT_ANY_THROW(P->getExpresionFormal());

    ASSERT_NO_THROW(P->setEstado("q2", false));
    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q2", true, 'a'));
    ASSERT_NO_THROW(P->setAlfabetoPila('a'));
    ASSERT_NO_THROW(P->setF("q1", 'a', '#', "q2", true, 'a'));
    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q2", true, 'a'));

    ASSERT_NO_THROW(P->setEstado("q3", false));
    ASSERT_NO_THROW(P->setEstado("q4", true));
    ASSERT_ANY_THROW(P->setEstado("q5", true));

    ASSERT_ANY_THROW(P->transicion('a'));

    ASSERT_NO_THROW(P->setAlfabeto('b'));
    ASSERT_ANY_THROW(P->setAlfabeto('c'));

    ASSERT_NO_THROW(P->setF("q2", 'a', 'a', "q2", true, 'a'));

    ASSERT_ANY_THROW(P->setF("q2", 'b', 'a', "q4", false, 'a'));
    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q2", false, 'a'));
    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q2", false, (char) 0));
    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q4", true, (char) 0));
    ASSERT_ANY_THROW(P->setF("q3", 'a', '#', "q3", false, (char) 0));

    ASSERT_ANY_THROW(P->setF("q1", 'a', '#', "q2", true, '#'));
    ASSERT_ANY_THROW(P->setF("q1", 'a', 'a', "q2", true, '#'));
    ASSERT_ANY_THROW(P->setF("q1", 'a', 'a', "q2", false, '#'));
    //quedamos en verificar que no se puedan anadir dos #

    ASSERT_NO_THROW(P->setF("q2", 'b', 'a', "q3", false, (char) 0));
    ASSERT_ANY_THROW(P->setF("q2", 'b', 'a', "q3", false, 'a'));
    ASSERT_NO_THROW(P->setF("q3", 'b', 'a', "q3", false, (char) 0));

    ASSERT_EQ(P->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), '#');

    ASSERT_NO_THROW(P->transicion('a'));

    ASSERT_EQ(P->getNombreEstadoActual(), "q2");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), 'a');

    ASSERT_NO_THROW(P->transicion('a'));

    ASSERT_EQ(P->getNombreEstadoActual(), "q2");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), 'a');

    ASSERT_NO_THROW(P->transicion('b'));

    ASSERT_EQ(P->getNombreEstadoActual(), "q3");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), 'a');

    ASSERT_NO_THROW(P->transicion('b'));
    ASSERT_EQ(P->getNombreEstadoActual(), "q3");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    EXPECT_EQ(P->getTopeDePila(), '#');

    ASSERT_ANY_THROW(P->setF("q1", 'b', '#', "q3", true, 'a'));

    ASSERT_NO_THROW(P->apagarAutomata());

    ASSERT_ANY_THROW(P->transicion('b'));
    ASSERT_ANY_THROW(P->setAlfabetoPila('b'));
    ASSERT_ANY_THROW(P->setAlfabeto('z'));
    ASSERT_ANY_THROW(P->setEstado("b", false));

    ASSERT_EQ(P->getNombreEstadoActual(), "q4");
    ASSERT_TRUE(P->getSituacionEstadoActual());
}

TEST(test_prueba, MTuring_Exceptions) {
    T = new MTuring(3, 2, 4, 'b');
    ASSERT_ANY_THROW(T->transicion());
    ASSERT_ANY_THROW(T->getExpresionFormal());
    ASSERT_ANY_THROW(T->getNombreEstadoInicial());
    ASSERT_ANY_THROW(T->getNombreEstadoActual());
    ASSERT_ANY_THROW(T->getSituacionEstadoActual());
    ASSERT_ANY_THROW(T->setEstadoInicial("q1"));

    ASSERT_EQ(T->getNroEstados(), 3);
    ASSERT_EQ(T->getNroElementosAlfabeto(), 2);
    EXPECT_EQ(T->getNroElementosAlfabetoCinta(), 4);

    ASSERT_EQ(T->getCopiaCinta(), "b");
    ASSERT_ANY_THROW(T->setAlfabetoCinta('b'));

    ASSERT_NO_THROW(T->setEstado("q0", false));
    ASSERT_ANY_THROW(T->setEstado("q0", true));

    ASSERT_NO_THROW(T->setEstadoInicial("q0"));
    ASSERT_EQ(T->getNombreEstadoInicial(), "q0");
    ASSERT_EQ(T->getNombreEstadoActual(), "q0");
    ASSERT_FALSE(T->getSituacionEstadoActual());

    ASSERT_NO_THROW(T->setAlfabeto('0'));
    ASSERT_ANY_THROW(T->setAlfabeto('0'));

    ASSERT_ANY_THROW(T->setEstadoInicial("q1"));
    ASSERT_ANY_THROW(T->setF("q0", '0', "q1", 'd', '0'));
    ASSERT_ANY_THROW(T->transicion());
    ASSERT_ANY_THROW(T->getExpresionFormal());

    ASSERT_NO_THROW(T->setEstado("q1", false));
    ASSERT_ANY_THROW(T->setF("q0", '0', "q1", 'd', '0'));

    ASSERT_NO_THROW(T->setAlfabetoCinta('0'));
    ASSERT_NO_THROW(T->setF("q0", '0', "q1", 'd', '0'));
    ASSERT_ANY_THROW(T->setF("q0", '0', "q1", 'd', '0'));

    ASSERT_NO_THROW(T->setEstado("q3", true));
    ASSERT_ANY_THROW(T->setEstado("q4", true));
    ASSERT_ANY_THROW(T->setEstado("q3", false));

    ASSERT_ANY_THROW(T->transicion());

    ASSERT_NO_THROW(T->setAlfabeto('1'));
    ASSERT_ANY_THROW(T->setAlfabeto('2'));

    ASSERT_ANY_THROW(T->setF("q0", '1', "q0", 'd', '1'));
    ASSERT_NO_THROW(T->setAlfabetoCinta('1'));
    ASSERT_NO_THROW(T->setF("q0", '1', "q0", 'd', '1'));
    ASSERT_ANY_THROW(T->setF("q0", '1', "q0", 'D', '1'));

    ASSERT_ANY_THROW(T->setF("q0", 'b', "q3", 'P', 'p'));
    ASSERT_NO_THROW(T->setAlfabetoCinta('p'));
    ASSERT_NO_THROW(T->setF("q0", 'b', "q3", 'P', 'p'));

    ASSERT_NO_THROW(T->setAlfabetoCinta('i'));
    ASSERT_ANY_THROW(T->setAlfabetoCinta('j'));
    ASSERT_ANY_THROW(T->setAlfabeto('j'));

    EXPECT_NO_THROW(T->getExpresionFormal());

    ASSERT_ANY_THROW(T->setF("q1", 'b', "q3", 'd', '1'));
    ASSERT_ANY_THROW(T->setF("q1", 'b', "q0", 'p', '1'));
    ASSERT_NO_THROW(T->setF("q1", 'b', "q3", 'p', 'i'));

    ASSERT_NO_THROW(T->setF("q1", '0', "q0", 'd', '0'));
    ASSERT_NO_THROW(T->setF("q1", '1', "q1", 'd', '1'));

    ASSERT_EQ(T->getCopiaCinta(), "b");
    //hasta ahora está definida toda la máquina que escribe i o p segun 0 pares o impares

    ASSERT_ANY_THROW(T->transicion());

    ASSERT_ANY_THROW(T->escribirCinta("1003"));
    ASSERT_EQ(T->getCopiaCinta(), "b");

    ASSERT_NO_THROW(T->escribirCinta("100"));
    ASSERT_EQ(T->getCopiaCinta(), "b100");

    ASSERT_ANY_THROW(T->escribirCinta("1003"));
    ASSERT_EQ(T->getCopiaCinta(), "b100");

    ASSERT_NO_THROW(T->escribirCinta("101"));
    ASSERT_EQ(T->getCopiaCinta(), "b100101");

    ASSERT_ANY_THROW(T->transicion());


    ASSERT_ANY_THROW(T->ponerCabezal(0));
    ASSERT_NO_THROW(T->setCintaLista());
    ASSERT_EQ(T->getCopiaCinta(), "b100101b");

    ASSERT_ANY_THROW(T->escribirCinta("10"));
    ASSERT_ANY_THROW(T->setCintaLista());
    ASSERT_ANY_THROW(T->transicion());

    EXPECT_EQ(T->getLecturaCabezal(), 'b');
    EXPECT_FALSE(T->isMaquinaParada());

    ASSERT_ANY_THROW(T->ponerCabezal(80));
    ASSERT_NO_THROW(T->ponerCabezal(1));
    ASSERT_ANY_THROW(T->ponerCabezal(2));
    EXPECT_EQ(T->getLecturaCabezal(), '1');

    ASSERT_NO_THROW(T->transicion());
    ASSERT_EQ(T->getLecturaCabezal(), '0');

    while (!T->isMaquinaParada()) {
        ASSERT_NO_THROW(T->transicion());
    }

    ASSERT_EQ("b100101ib", T->getCopiaCinta());

    ASSERT_ANY_THROW(T->transicion());
    ASSERT_ANY_THROW(T->setCintaLista());
}