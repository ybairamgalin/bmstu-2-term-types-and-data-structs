cmake_minimum_required(VERSION 3.17)
project(bmstu_2_term_types_and_data_structs C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "-Wall -Werror -O0")

#include_directories(lab_03)

#include_directories(lab_03/inc)
#
#add_executable(bmstu_2_term_types_and_data_structs
#        lab_03/inc/sparse_matrix.h
#        lab_03/src/main.c
#        lab_03/src/sparse_matrix.c
#        lab_03/src/matrix.c
#        lab_03/inc/matrix.h
#        lab_03/src/measure_time.c
#        lab_03/inc/measure_time.h
#        )

include_directories(lab_06/inc)

add_executable(lab_06
        lab_06/src/main.c
        lab_06/src/hash_table.c
        lab_06/inc/hash_table.h
        lab_06/src/bin_tree.c
        lab_06/inc/bin_tree.h
        lab_06/src/data.c
        lab_06/inc/data.h)
