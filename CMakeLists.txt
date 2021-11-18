cmake_minimum_required(VERSION 3.17)
project(bmstu_2_term_types_and_data_structs C)

set(CMAKE_C_STANDARD 99)

#include_directories(lab_03)
include_directories(lab_04/inc)

add_executable(bmstu_2_term_types_and_data_structs
        lab_04/src/main.c
        lab_04/src/stack.c
        lab_04/inc/stack.h
        )