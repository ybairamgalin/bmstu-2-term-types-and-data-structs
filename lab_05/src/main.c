#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "service_simulation.h"


#define MAX_INPUT_SZ 100

int input_long(long *value)
{
    char input[MAX_INPUT_SZ];

    if (fgets(input, MAX_INPUT_SZ, stdin) == NULL)
    {
        printf("Input error\n");
        return EXIT_FAILURE;
    }

    if (input[strlen(input) - 1] != '\n')
    {
        printf("Input too long\n");
        return EXIT_FAILURE;
    }

    input[strlen(input) - 1] = '\0';
    char *err;
    *value = strtol(input, &err, 10);

    if (err == input)
    {
        printf("Not a number\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    long gen_time_first, handle_time_first, handle_time_second;

    printf("Input max generation time of first type request (integer from 1 to 100): ");

    if (input_long(&gen_time_first) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (gen_time_first <= 0 || gen_time_first > 100)
    {
        printf("An integer from 1 to 100 should be specified\n");
        return EXIT_FAILURE;
    }

    printf("Input max handling time of first type request (integer from 1 to 100): ");

    if (input_long(&handle_time_first) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (handle_time_first <= 0 || handle_time_first > 100)
    {
        printf("An integer from 1 to 100 should be specified\n");
        return EXIT_FAILURE;
    }

    printf("Input max handling time of second type request (integer from 1 to 100): ");

    if (input_long(&handle_time_second) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (handle_time_second <= 0 || handle_time_second > 100)
    {
        printf("An integer from 1 to 100 should be specified\n");
        return EXIT_FAILURE;
    }

    set_simulation_parameters((int)handle_time_first, (int)handle_time_second,
                              (int)gen_time_first);
    simulation_start();
    long show_info;
    printf("Do you want to see memory info of %d last allocations and frees (1/0)? ", 100);

    if (input_long(&show_info) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    if (show_info == 1)
        print_mem_info();

    return EXIT_SUCCESS;
}
