#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/subscriber.h"
#include "../inc/subscriber_info.h"
#include "../inc/address.h"
#include "../inc/common.h"

int input_last_name(char *dest)
{
    printf("Введите фамилию (строка 1-%d символов): ", MAX_NAME_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_NAME_LNG)))
        return error;
}

int input_first_name(char *dest)
{
    printf("Введите имя (строка 1-%d символов): ", MAX_NAME_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_NAME_LNG)))
        return error;

    return EXIT_SUCCESS;
}

int input_phone(char *dest)
{
    printf("Введите номер телефона (строка 1-%d символов): ",
           MAX_PHONE_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_NAME_LNG)))
        return error;

    return EXIT_SUCCESS;
}

int input_subscriber(subscriber_t *sub)
{
    int error;

    if ((error = input_first_name(sub->first_name)) != EXIT_SUCCESS)
        return error;

    if ((error = input_last_name(sub->last_name)) != EXIT_SUCCESS)
        return error;

    if ((error = input_phone(sub->phone)) != EXIT_SUCCESS)
        return error;

    if ((error = input_address(&(sub->address))) != EXIT_SUCCESS)
        return error;

    return EXIT_SUCCESS;
}

void print_subscriber(const subscriber_t sub)
{
    printf("%s\t", sub.first_name);
    printf("%s\t", sub.last_name);
    printf("%s\t", sub.phone);
    printf("\n");
}
