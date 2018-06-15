cmake_minimum_required(VERSION 3.10)
project(AFD)

set(CMAKE_CXX_STANDARD 11)

add_executable(AFD main.cpp AFD.cpp AFD.h Data_Structures/Stack.h Data_Structures/Node.h Automata.cpp Automata.h APila.cpp APila.h Data_Structures/Celda.h Data_Structures/Cinta.h MTuring.h MTuring.cpp funcionesMain.cpp funcionesMain.h)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_subdirectory(test)

set(MS_TEST_SOURCE_FILES Automata.h Automata.cpp AFD.h AFD.cpp APila.h APila.cpp)
add_executable(MS_Test ${MS_TEST_SOURCE_FILES})