#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "big_float.h"
#include "errors.h"

int is_float(const char *str)
{
    regex_t int_regex;

    if ((regcomp(&int_regex, FLOAT_REGEX, REG_EXTENDED)) != OK)
        exit(ERR_REGEX_COMP);

    if (regexec(&int_regex, str, 0, NULL, 0) != OK)
        return 0;

    return 1;
}

void set_sign(const char *str, size_t *pos, int *field)
{
    if (str[*pos] == '+')
    {
        *field = 1;
        (*pos)++;
    }
    else if (str[*pos] == '-')
    {
        *field = -1;
        (*pos)++;
    }
    else
        *field = 1;
}
void shift_arr_left(int *arr, const int from, const int arr_sz)
{
    for (int i = from; i < arr_sz; i++)
        arr[i] = arr[i + 1];
}

void shift_arr_right(int *arr, const int from, const int arr_sz)
{
    for (int i = arr_sz - 1; i >= from; i--)
        arr[i + 1] = arr[i];
}

int is_zero(big_float_t elem)
{
    for (size_t i = 0; i < elem.mantissa_lng; i++)
        if (elem.digits[i] != 0)
            return 0;

    return 1;
}

void set_zero(big_float_t *elem)
{
    elem->sign = 1;
    elem->digits[0] = 0;
    elem->digits[1] = 0;
    elem->mantissa_lng = 2;
    elem->exp_value = 1;
}

void trim(big_float_t *elem)
{
    while (elem->digits[0] == 0 && elem->mantissa_lng > 1)
    {
        shift_arr_left(elem->digits, 0, (elem->mantissa_lng)--);
        (elem->exp_value)--;
    }

    for (size_t i = elem->mantissa_lng - 1;
            elem->digits[i] == 0 && elem->mantissa_lng > 1; i--)
        elem->mantissa_lng--;


    shift_arr_right(elem->digits, 0, (elem->mantissa_lng)++);
    elem->digits[0] = 0;
    (elem->exp_value)++;
}

int str_to_big_float_t(big_float_t *dest, const char *str) {
    if (!is_float(str))
        return ERR_INVALID_FLOAT_FORMAT;

    size_t pos = 0;
    set_sign(str, &pos, &(dest->sign));

    dest->mantissa_lng = 0;
    int nums_before_dot = 0;

    for (; isdigit((unsigned char)str[pos]); pos++, (dest->mantissa_lng)++, nums_before_dot++)
    {
        if (dest->mantissa_lng >= MAX_MANTISSA_LNG)
            return ERR_INVALID_FLOAT_FORMAT;

        dest->digits[dest->mantissa_lng] = str[pos] - ZERO_ASCII_CODE;
    }

    if (str[pos] == '.')
    {
        pos++;

        for (; isdigit((unsigned char)str[pos]); pos++, (dest->mantissa_lng)++)
        {
            if (dest->mantissa_lng >= MAX_MANTISSA_LNG)
                return ERR_INVALID_FLOAT_FORMAT;

            dest->digits[dest->mantissa_lng] = str[pos] - ZERO_ASCII_CODE;
        }
    }

    dest->exp_value = 0;

    if (str[pos] == 'e' || str[pos] == 'E')
    {
        int exp_sign;

        pos++;
        set_sign(str, &pos, &exp_sign);

        for (; isdigit((unsigned char)str[pos]); pos++)
            dest->exp_value = dest->exp_value * 10 + str[pos] - ZERO_ASCII_CODE;

        dest->exp_value *= exp_sign;
    }

    dest->exp_value += nums_before_dot - 1;
    trim(dest);

    if (is_zero(*dest))
        set_zero(dest);

    return OK;
}

void print_big_float(const big_float_t elem)
{
    printf((elem.sign == 1) ? "+" : "-");
    printf("%d", elem.digits[0]);
    printf((elem.mantissa_lng > 1 ) ? "." : "");

    for (size_t i = 1; i < elem.mantissa_lng; i++)
        printf("%d", elem.digits[i]);

    printf("e%c%d\n", (elem.exp_value >= 0 ) ? '+' : '-', abs(elem.exp_value));
}
