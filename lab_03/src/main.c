#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include "sparse_matrix.h"
#include "measure_time.h"

int main(void)
{
    setbuf(stdout, NULL);

    int user_input;
    printf("1 - sparse\n2 - time it!\n0 - exit\n");

    if (scanf("%d", &user_input) != 1)
        return EXIT_FAILURE;

    if (user_input == 1)
        sparse_matrix_start();
    else if (user_input == 2)
        eval_time();

    return EXIT_SUCCESS;
}
