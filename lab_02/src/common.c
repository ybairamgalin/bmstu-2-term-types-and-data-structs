#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/common.h"

int input_string(char *dest, const int max_lng)
{
    if (fgets(dest, max_lng, stdin) == NULL)
        return EXIT_FAILURE;

    if (dest[strlen(dest) - 1] != '\n')
    {
        printf("Превышена допустимая длина строки\n");
        return EXIT_FAILURE;
    }

    dest[strlen(dest) - 1] = '\0';

    if (strlen(dest) == 0)
    {
        printf("Пустой ввод\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}