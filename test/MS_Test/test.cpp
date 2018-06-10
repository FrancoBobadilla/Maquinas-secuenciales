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

TEST(test_prueba, MTuring_ParOImpar) {
// escribe P en la cinta si hay una cantidad par de 0
    // escribe I si la cantidade de 0 es impar

    M = new MTuring(1, 2, 4, '/');
    ASSERT_EQ(1, M->getNroEstados());
    ASSERT_EQ(2, M->getNroElementosAlfabeto());
//    ASSERT_EQ(4, M->getNroElementosAlfabetoCinta());
//    ASSERT_EQ('/', M.getBlanco());
    ASSERT_EQ(M->getLecturaCabezal(), '/');
}

