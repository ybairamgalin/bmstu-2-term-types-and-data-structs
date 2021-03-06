#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include "sparse_matrix.h"
#include "measure_time.h"

int main(void)
{
    setbuf(stdout, NULL);

    char user_string[128];
    printf("Yaroslav Bairamgalin | BMSTU 2021\n");
    printf("This program should be used to add 2 matrices in sparse form "
           "and/or evaluate time of such operation in comparison with "
           "regular matrix representation.\n\n");
    printf("1 - add sparse matrices\n2 - evaluate time and memory!\n0 - exit\n");

    if (fgets(user_string, sizeof(user_string), stdin) == NULL)
        return EXIT_FAILURE;

    char *end;
    long user_input = strtol(user_string, &end, 10);

    if (end == user_string)
    {
        printf("Input error\n");
        return EXIT_FAILURE;
    }

    if (user_input == 1)
        sparse_matrix_start();
    else if (user_input == 2)
        eval_time();
    else if (user_input == 0)
        printf("Exit\n");
    else
    {
        printf("Input error\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
