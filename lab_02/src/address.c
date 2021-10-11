#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/address.h"
#include "../inc/common.h"

int input_city(char *dest)
{
    printf("Введите город (строка 1-%d символов): ",
           MAX_ADDRESS_FIELD_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_ADDRESS_FIELD_LNG)))
        return error;

    return EXIT_SUCCESS;
}

int input_street(char *dest)
{
    printf("Введите улицу (строка 1-%d символов): ",
           MAX_ADDRESS_FIELD_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_ADDRESS_FIELD_LNG)))
        return error;

    return EXIT_SUCCESS;
}

int input_house(char *dest)
{
    printf("Введите дом (строка 1-%d символов): ",
           MAX_ADDRESS_FIELD_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_ADDRESS_FIELD_LNG)))
        return error;

    return EXIT_SUCCESS;
}

int input_apartment(char *dest)
{
    printf("Введите квартиру (строка 1-%d символов): ",
           MAX_ADDRESS_FIELD_LNG - 2);
    int error;

    if ((error = input_string(dest, MAX_ADDRESS_FIELD_LNG)))
        return error;

    return EXIT_SUCCESS;
}

int input_address(address_t *address)
{
    int error;

    if ((error = input_city(address->city)) != EXIT_SUCCESS)
        return error;

    if ((error = input_street(address->street)) != EXIT_SUCCESS)
        return error;

    if ((error = input_house(address->house)) != EXIT_SUCCESS)
        return error;

    if ((error = input_apartment(address->apartment)) != EXIT_SUCCESS)
        return error;

    return EXIT_SUCCESS;
}
