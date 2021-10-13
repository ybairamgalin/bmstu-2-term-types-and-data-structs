#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/subscriber_info.h"
#include "../inc/common.h"
#include "../inc/subscriber.h"

int input_status(status_t *status)
{
    printf("Ввдеите статус personal (для личного) или "
           "company (для служебного)): ");

    int error;
    char input[MAX_COMPANY_INFO_LNG];

    if ((error = input_string(input, MAX_COMPANY_INFO_LNG)) != EXIT_SUCCESS)
        return error;

    if (strcmp(input, "personal") == 0)
        *status = personal;
    else if (strcmp(input, "company") == 0)
        *status = company;
    else
        return ERR_SUB_INPUT_ERR;

    return EXIT_SUCCESS;
}

int input_personal(personal_info_t *personal_info)
{
    printf("Дата рождения. Во время ввода даты рождения необходимо указать "
           "3 беззнаковых целых числа: день, месяц, год\n");

    int day, month, year;

    printf("Введите день: ");

    if (scanf("%d", &day) != 1)
        return ERR_SUB_INPUT_ERR;

    if (day < 1 || day > 31)
        return ERR_SUB_INPUT_ERR;

    printf("Введите месяц: ");

    if (scanf("%d", &month) != 1)
        return ERR_SUB_INPUT_ERR;

    if (month < 1 || month > 12)
        return ERR_SUB_INPUT_ERR;

    printf("Введите год: ");

    if (scanf("%d", &year) != 1)
        return ERR_SUB_INPUT_ERR;

    if (year > 2021 || year < 1800)
        return ERR_SUB_INPUT_ERR;

    personal_info->birth_date.day = day;
    personal_info->birth_date.month = month;
    personal_info->birth_date.year = year;

    return EXIT_SUCCESS;
}

int input_company(company_info_t *company_info)
{
    printf("Введите название компании: ");

    int error;

    if ((error = input_string(company_info->name, MAX_COMPANY_INFO_LNG))
            != EXIT_SUCCESS)
        return error;

    printf("Введите должность: ");

    if ((error = input_string(company_info->position, MAX_COMPANY_INFO_LNG))
            != EXIT_SUCCESS)
        return error;

    return EXIT_SUCCESS;
}

int input_sub_info(status_t *status, subscriber_info_t *info)
{
    int error;

    if ((error = input_status(status)) != EXIT_SUCCESS)
        return error;

    if (*status == personal)
    {
        if ((error = input_personal(&(info->person_info))) != EXIT_SUCCESS)
            return error;
    }
    else if (*status == company)
    {
        if ((error = input_company(&(info->company_info))) != EXIT_SUCCESS)
            return error;
    }
    else
        exit(1);

    return EXIT_SUCCESS;
}

void print_sub_info(const status_t status, const subscriber_info_t info)
{
    if (status == personal)
    {
        printf("Статус:\t\tpersonal\n");
        printf("Дата рожд.:\t%d.%d.%d\n", info.person_info.birth_date.day,
               info.person_info.birth_date.month,
               info.person_info.birth_date.year);
    }
    else if (status == company)
    {
        printf("Статус:\t\tcompany\n");
        printf("Название:\t%s\n"
               "Должность:\t%s\n", info.company_info.name,
               info.company_info.position);
    }
}
