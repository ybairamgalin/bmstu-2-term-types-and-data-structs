cmake_minimum_required(VERSION 3.17)
project(bmstu_2_term_types_and_data_structs C)

set(CMAKE_C_STANDARD 99)

include_directories(lab_03)

add_executable(bmstu_2_term_types_and_data_structs
        inc/sparse_matrix.h
        src/main.c
        src/sparse_matrix.c
)
