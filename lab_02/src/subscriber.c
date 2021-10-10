#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/subscriber.h"
#include "../inc/subscriber_info.h"
#include "../inc/address.h"

#define ERR_NAME_INPUT 1

int input_last_name(char *dest)
{
    printf("Введите фамилию (строка 1-%d символов): ", MAX_NAME_LNG - 2);

    if (fgets(dest, sizeof(dest), stdin) == NULL)
        return ERR_NAME_INPUT;

    if (dest[strlen(dest) - 1] != '\n')
    {
        printf("Превышена допустимая длина строки\n");
        return ERR_NAME_INPUT;
    }

    dest[strlen(dest) - 1] = '\0';

    if (strlen(dest) == 0)
    {
        printf("Пустой ввод\n");
        return ERR_NAME_INPUT;
    }

    return EXIT_SUCCESS;
}

int input_first_name(char *dest)
{
    printf("Введите имя (строка 1-%d символов): ", MAX_NAME_LNG - 2);

    if (fgets(dest, sizeof(dest), stdin) == NULL)
        return ERR_NAME_INPUT;

    if (dest[strlen(dest) - 1] != '\n')
    {
        printf("Превышена допустимая длина строки\n");
        return ERR_NAME_INPUT;
    }

    dest[strlen(dest) - 1] = '\0';

    if (strlen(dest) == 0)
    {
        printf("Пустой ввод\n");
        return ERR_NAME_INPUT;
    }

    return EXIT_SUCCESS;
}

int input_subscriber(subscriber_t *sub)
{
    int error;

    if ((error = input_first_name(sub->first_name)))
        return error;

    if ((error = input_last_name(sub->last_name)))
        return error;


    return EXIT_SUCCESS;
}

void print_subscriber(const subscriber_t sub)
{
    printf("%s\t", sub.first_name);
    printf("%s\t", sub.last_name);
    printf("\n");
}
