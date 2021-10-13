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

    if ((error = input_sub_info(&(sub->status), &(sub->subscriber_info)))
        != EXIT_SUCCESS)
        return error;

    return EXIT_SUCCESS;
}

void print_subscriber(const subscriber_t sub)
{
    printf("Имя:\t\t%s\n", sub.first_name);
    printf("Фамилия:\t%s\n", sub.last_name);
    printf("Телефон:\t%s\n", sub.phone);
    print_address(sub.address);
    print_sub_info(sub.status, sub.subscriber_info);
    printf("\n");
}

int sub_last_name_cmp(const void *sub_1, const void *sub_2)
{
    subscriber_t sub_a = *(const subscriber_t*)sub_1;
    subscriber_t sub_b = *(const subscriber_t*)sub_2;

    return strcmp(sub_a.last_name, sub_b.last_name);
}

int sub_first_name_cmp(const void *sub_1, const void *sub_2)
{
    subscriber_t sub_a = *(const subscriber_t*)sub_1;
    subscriber_t sub_b = *(const subscriber_t*)sub_2;

    return strcmp(sub_a.first_name, sub_b.first_name);
}

int has_birthday_soon(const subscriber_t subscriber)
{
    if (subscriber.status == company)
        return 0;

    if (subscriber.subscriber_info.person_info.birth_date.month != 10)
        return 0;

    if (subscriber.subscriber_info.person_info.birth_date.day > 19 ||
            subscriber.subscriber_info.person_info.birth_date.day < 12)
        return 0;

    return 1;
}
