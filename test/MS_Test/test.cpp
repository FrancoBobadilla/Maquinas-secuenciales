#include <include/gtest/gtest.h>

#include "../../Automata.h"
#include "../../Automata.cpp"
#include "../../AFD.h"
#include "../../AFD.cpp"
#include "../../APila.h"
#include "../../APila.cpp"
#include "../../MTuring.h"
#include "../../MTuring.cpp"

#include "../../Data_Structures/Celda.h"
#include "../../Data_Structures/Cinta.h"
#include "../../Data_Structures/Node.h"
#include "../../Data_Structures/Stack.h"

AFD *F;
APila *P;
MTuring *T;

TEST(test_prueba, AFD_Exceptions) {
    F = new AFD(2, 3);
    ASSERT_ANY_THROW(F->transicion());
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
    ASSERT_ANY_THROW(F->transicion());
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

    ASSERT_ANY_THROW(F->transicion());

    ASSERT_ANY_THROW(F->setCadenaAnalizar("aaaz"));
    ASSERT_NO_THROW(F->setCadenaAnalizar("bacbc"));
    ASSERT_ANY_THROW(F->setCadenaAnalizar("a"));

    ASSERT_ANY_THROW(F->transicion());

    ASSERT_NO_THROW(F->setF("q1", 'c', "q1"));
    ASSERT_NO_THROW(F->setF("q2", 'b', "q1"));
    ASSERT_NO_THROW(F->setF("q2", 'a', "q2"));
    ASSERT_NO_THROW(F->setF("q2", 'c', "q2"));

    //afd que da salida con b impares

    ASSERT_ANY_THROW(F->setF("q2", 'd', "q2"));
    ASSERT_ANY_THROW(F->setF("q2", 'c', "q2"));


    ASSERT_NO_THROW(F->transicion());
    ASSERT_EQ(F->getNombreEstadoActual(), "q2");
    ASSERT_TRUE(F->getSituacionEstadoActual());

    ASSERT_NO_THROW(F->transicion());
    ASSERT_EQ(F->getNombreEstadoActual(), "q2");
    ASSERT_TRUE(F->getSituacionEstadoActual());
    ASSERT_NO_THROW(F->transicion());
    ASSERT_EQ(F->getNombreEstadoActual(), "q2");
    ASSERT_TRUE(F->getSituacionEstadoActual());

    ASSERT_EQ(F->getNombreEstadoInicial(), "q1");

    ASSERT_NO_THROW(F->transicion());

    ASSERT_NO_THROW(F->transicion());
    ASSERT_EQ(F->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(F->getSituacionEstadoActual());
    ASSERT_ANY_THROW(F->transicion());
    ASSERT_EQ(F->getNombreEstadoActual(), "q1");
    ASSERT_FALSE(F->getSituacionEstadoActual());

    ASSERT_ANY_THROW(F->setEstadoInicial("q2"));
    ASSERT_ANY_THROW(F->setEstado("q2", true));
    ASSERT_ANY_THROW(F->setAlfabeto('c'));

}

TEST(test_prueba, APila_Exceptions) {
    P = new APila(4, 2, 1, '#');
    ASSERT_ANY_THROW(P->transicion());
    ASSERT_ANY_THROW(P->getExpresionFormal());
    ASSERT_ANY_THROW(P->getNombreEstadoInicial());
    ASSERT_ANY_THROW(P->getNombreEstadoActual());
    ASSERT_ANY_THROW(P->getSituacionEstadoActual());
    ASSERT_ANY_THROW(P->setEstadoInicial("q1"));

    ASSERT_EQ(P->getNroEstados(), 4);
    ASSERT_EQ(P->getNroElementosAlfabeto(), 2);
    EXPECT_EQ(P->getNroElementosAlfabetoPila(), 1);

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
    ASSERT_ANY_THROW(P->transicion());
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

    ASSERT_ANY_THROW(P->transicion());

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

    ASSERT_ANY_THROW(P->transicion());

    ASSERT_NO_THROW(P->setCadenaAnalizar("aabb"));

    ASSERT_NO_THROW(P->transicion());

    ASSERT_EQ(P->getNombreEstadoActual(), "q2");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), 'a');

    ASSERT_NO_THROW(P->transicion());

    ASSERT_EQ(P->getNombreEstadoActual(), "q2");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), 'a');

    ASSERT_NO_THROW(P->transicion());

    ASSERT_EQ(P->getNombreEstadoActual(), "q3");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    ASSERT_EQ(P->getTopeDePila(), 'a');

    ASSERT_NO_THROW(P->transicion());
    ASSERT_EQ(P->getNombreEstadoActual(), "q3");
    ASSERT_FALSE(P->getSituacionEstadoActual());
    EXPECT_EQ(P->getTopeDePila(), '#');

    ASSERT_ANY_THROW(P->setF("q1", 'b', '#', "q3", true, 'a'));

//    ASSERT_NO_THROW(P->apagarAutomata());

    //esta es la transicion lambda
    ASSERT_NO_THROW(P->transicion());
    ASSERT_ANY_THROW(P->setAlfabetoPila('b'));
    ASSERT_ANY_THROW(P->setAlfabeto('z'));
    ASSERT_ANY_THROW(P->setEstado("b", false));

    // al momento de ejecutar, el automata ya está apagado
    ASSERT_ANY_THROW(P->transicion());

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

    ASSERT_ANY_THROW(T->setCadenaAnalizar("1003"));
    ASSERT_EQ(T->getCopiaCinta(), "b");

    ASSERT_ANY_THROW(T->ponerCabezal(0));
    ASSERT_NO_THROW(T->setCadenaAnalizar("100101"));
    ASSERT_EQ(T->getCopiaCinta(), "b100101b");

    ASSERT_ANY_THROW(T->setCadenaAnalizar("1003"));
    ASSERT_EQ(T->getCopiaCinta(), "b100101b");

    ASSERT_ANY_THROW(T->transicion());


    ASSERT_NO_THROW(T->ponerCabezal(1));
    ASSERT_EQ(T->getCopiaCinta(), "b100101b");
    // aca la maquina tiene la cinta llena y el cabezal puesto
    // la maquina esta lista

    ASSERT_ANY_THROW(T->setCadenaAnalizar("10"));
    ASSERT_ANY_THROW(T->ponerCabezal(1));

    ASSERT_EQ(T->getLecturaCabezal(), '1');

    ASSERT_NO_THROW(T->transicion());
    EXPECT_EQ(T->getNombreEstadoActual(), "q0");
    EXPECT_EQ(T->getLecturaCabezal(), '0');
    EXPECT_FALSE(T->isAutomataApagado());

    ASSERT_ANY_THROW(T->ponerCabezal(80));
    ASSERT_ANY_THROW(T->ponerCabezal(1));
    ASSERT_ANY_THROW(T->ponerCabezal(2));

    ASSERT_NO_THROW(T->transicion());
    EXPECT_EQ(T->getNombreEstadoActual(), "q1");
    ASSERT_EQ(T->getLecturaCabezal(), '0');

    while (!T->isAutomataApagado()) {
        ASSERT_NO_THROW(T->transicion());
    }

    ASSERT_EQ("b100101ib", T->getCopiaCinta());

    ASSERT_ANY_THROW(T->transicion());
    ASSERT_ANY_THROW(T->setCadenaAnalizar("111"));
}

TEST(Ejercicios_Guia, AFD_aImpar_bPar) {
    // consigna: hallar un AFD que acepte que w tenga un numero impar de a y par de b
    F = new AFD(4, 2);
    ASSERT_NO_THROW(F->setEstado("C0", false));
    ASSERT_NO_THROW(F->setEstado("C1", false));
    ASSERT_NO_THROW(F->setEstado("C2", false));
    ASSERT_NO_THROW(F->setEstado("C3", true));

    ASSERT_NO_THROW(F->setAlfabeto('a'));
    ASSERT_NO_THROW(F->setAlfabeto('b'));

    ASSERT_NO_THROW(F->setF("C0", 'a', "C3"));
    ASSERT_NO_THROW(F->setF("C0", 'b', "C1"));

    ASSERT_NO_THROW(F->setF("C1", 'a', "C2"));
    ASSERT_NO_THROW(F->setF("C1", 'b', "C0"));

    ASSERT_NO_THROW(F->setF("C2", 'a', "C1"));
    ASSERT_NO_THROW(F->setF("C2", 'b', "C3"));

    ASSERT_NO_THROW(F->setF("C3", 'a', "C0"));
    ASSERT_NO_THROW(F->setF("C3", 'b', "C2"));

    ASSERT_NO_THROW(F->setCadenaAnalizar("aaabbbb"));

    ASSERT_NO_THROW(F->setEstadoInicial("C0"));

    while (!F->isAutomataApagado()) {
        cout << F->getNombreEstadoActual() << "\n";
        F->transicion();
    }

    EXPECT_EQ(F->getNombreEstadoActual(), "C3");
    EXPECT_TRUE(F->getSituacionEstadoActual());
    EXPECT_TRUE(F->isAutomataApagado());

    string tmp = F->getExpresionFormal();
}

TEST(Ejercicios_Guia, APila_nibbles) {
    //Consigna: dos nibbles separados por un * donde el primero tiene la misma cantidad de 1 que el segundo de 0
    P = new APila(4, 3, 1, '#');

    P->setEstado("q0", false);
    P->setEstado("q1", false);
    P->setEstado("q2", false);
    P->setEstado("q3", true);

    P->setEstadoInicial("q0");

    P->setAlfabeto('0');
    P->setAlfabeto('1');
    P->setAlfabeto('*');

    P->setAlfabetoPila('a');

    P->setF("q0", '0', '#', "q0", true, (char) 0);
    P->setF("q0", '0', 'a', "q0", true, (char) 0);
    P->setF("q0", '1', '#', "q1", true, 'a');
    P->setF("q0", '*', '#', "q2", true, (char) 0);
    P->setF("q0", '*', 'a', "q2", true, (char) 0);

    P->setF("q1", '1', 'a', "q1", true, 'a');
    P->setF("q1", '0', 'a', "q1", true, (char) 0);
    P->setF("q1", '*', 'a', "q2", true, (char) 0);

    P->setF("q2", '0', 'a', "q2", false, (char) 0);
    P->setF("q2", '1', 'a', "q2", true, (char) 0);
    P->setF("q2", '1', '#', "q2", true, (char) 0);

    ASSERT_ANY_THROW(P->setF("q2", '0', '#', "q3", true, char(0)));

    P->setCadenaAnalizar("1110*0100");

    cout << P->getNombreEstadoActual() << "\n";

    while (!P->isAutomataApagado()) {
        ASSERT_NO_THROW(P->transicion());
        cout << P->getNombreEstadoActual() << "\n";
    }

    EXPECT_EQ(P->getNombreEstadoActual(), "q3");
    EXPECT_TRUE(P->getSituacionEstadoActual());
    EXPECT_TRUE(P->isAutomataApagado());

    string tmp = P->getExpresionFormal();
}

TEST(Ejercicios_Guia, MT_incremento) {
    T = new MTuring(6, 3, 3, 'b');

    string a[] = {"q0", "q1", "q2", "q3", "q4", "q5"};
    for (int i = 0; i < 6; ++i)
        T->setEstado(a[i], i == 4);
    T->setEstadoInicial("q0");

    T->setAlfabeto('0');
    T->setAlfabeto('1');
    T->setAlfabeto('$');
    T->setAlfabetoCinta('0');
    T->setAlfabetoCinta('1');
    T->setAlfabetoCinta('$');

    T->setF("q0", '0', "q0", 'd', '0');
    T->setF("q0", '1', "q0", 'd', '1');
    T->setF("q0", 'b', "q1", 'i', 'b');
    T->setF("q0", '$', "q0", 'd', '$');

    T->setF("q1", '0', "q2", 'i', '1');
    T->setF("q1", '1', "q3", 'i', '0');

    T->setF("q2", '0', "q2", 'i', '0');
    T->setF("q2", '1', "q2", 'i', '1');
    T->setF("q2", '$', "q5", 'd', '$');

    T->setF("q3", '0', "q2", 'i', '1');
    T->setF("q3", '1', "q3", 'i', '0');
    T->setF("q3", '$', "q4", 'p', '1');

    T->setF("q5", '0', "q4", 'p', '0');
    T->setF("q5", '1', "q4", 'p', '1');

    T->setCadenaAnalizar("$1111");
    T->ponerCabezal(1);

    cout << T->getNombreEstadoActual() << "\n";
    cout << T->getCopiaCinta() << "\n";

    while (!T->isAutomataApagado()) {
        ASSERT_NO_THROW(T->transicion());
        cout << T->getNombreEstadoActual() << "\n";
        cout << T->getCopiaCinta() << "\n";
    }

    EXPECT_EQ(T->getNombreEstadoActual(), "q4");
    EXPECT_TRUE(T->getSituacionEstadoActual());
    EXPECT_TRUE(T->isAutomataApagado());
    EXPECT_EQ(T->getCopiaCinta(), "b10000b");

    string tmp = T->getExpresionFormal();
}