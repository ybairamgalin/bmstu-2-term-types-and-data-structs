cmake_minimum_required(VERSION 3.17)
project(bmstu_2_term_types_and_data_structs C)

set(CMAKE_C_STANDARD 99)

#include_directories(lab_03)

# include_directories(lab_04/inc)

add_executable(bmstu_2_term_types_and_data_structs
        lab_04/src/main.c
        lab_04/src/stack.c
        lab_04/inc/stack.h
        )

# include_directories(lab_03/inc)

add_executable(bmstu_2_term_types_and_data_structs
        lab_03/inc/sparse_matrix.h
        lab_03/src/main.c
        lab_03/src/sparse_matrix.c
        lab_03/src/matrix.c
        lab_03/inc/matrix.h
        lab_03/src/measure_time.c
        lab_03/inc/measure_time.h
        )
