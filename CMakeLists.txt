cmake_minimum_required(VERSION 3.10)
project(AFD)

set(CMAKE_CXX_STANDARD 11)

add_executable(AFD main.cpp AFD.cpp AFD.h Estado.cpp Estado.h Data_Structures/Stack.h Data_Structures/Node.h)