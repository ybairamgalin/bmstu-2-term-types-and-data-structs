#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack.h>



int main(void)
{
    printf("Yaroslav Bairamgalin | BMSTU 2021\n");
    printf("Program receives 2 sets of integers, puts them in 2 stacks "
           "and than sorts. Two stack types are available: list and static "
           "array.\n");
    printf("1 - use stack based on list\n2 - use stack based on array\n"
           "0 - exit\n");

    char user_input[MAX_USER_INPUT_LNG];

    if (fgets(user_input, sizeof(user_input), stdin) == NULL)
    {
        printf("Input failure\n");
        return EXIT_FAILURE;
    }

    if (user_input[strlen(user_input) - 1] != '\n')
    {
        printf("Input too long\n");
        return EXIT_FAILURE;
    }

    user_input[strlen(user_input) - 1] = '\0';

    char *end;
    long value = strtol(user_input, &end, 10);

    if (end == user_input)
    {
        printf("Input error\n");
        return EXIT_FAILURE;
    }

    if (value == 1)
    {
        if (stack_start() != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }
    else if (value == 2)
    {
        if (arr_stack_start() != EXIT_SUCCESS)
            return EXIT_FAILURE;
    }
    else if (value == 0)
        return EXIT_SUCCESS;
    else
    {
        printf("Input error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
