#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "big_float.h"
#include "errors.h"

int is_float(const char *str)
{
    regex_t float_regex;

    if ((regcomp(&float_regex, FLOAT_REGEX, REG_EXTENDED)) != OK)
        exit(ERR_REGEX_COMP);

    if (regexec(&float_regex, str, 0, NULL, 0) != OK)
        return 0;

    return 1;
}

int is_int(const char *str)
{
    regex_t int_regex;

    if ((regcomp(&int_regex, INT_REGEX, REG_EXTENDED)) != OK)
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
    for (int i = from; i < arr_sz - 1; i++)
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

big_float_t empty()
{
    big_float_t elem;
    elem.sign = 1;
    elem.mantissa_lng = 0;
    elem.exp_value = 0;

    for (size_t i = 0; i < MAX_MANTISSA_LNG; i++)
        elem.digits[i] = 0;

    return elem;
}

int str_to_big_float_t(big_float_t *dest, const char *str) {
    if (!is_float(str))
    {
        printf("\n\nВвденное число не соответствует формату вещественного числа.");
        return ERR_INVALID_FLOAT_FORMAT;
    }
    *dest = empty();
    size_t pos = 0;
    set_sign(str, &pos, &(dest->sign));

    int nums_before_dot = 0;

    for (; isdigit((unsigned char)str[pos]); pos++, (dest->mantissa_lng)++, nums_before_dot++)
    {
        if (dest->mantissa_lng >= MAX_MANTISSA_LNG)
        {
            printf("\n\nПревышена допустимая длина строки");
            return ERR_INVALID_FLOAT_FORMAT;
        }

        dest->digits[dest->mantissa_lng] = str[pos] - ZERO_ASCII_CODE;
    }

    if (str[pos] == '.')
    {
        pos++;

        for (; isdigit((unsigned char)str[pos]); pos++, (dest->mantissa_lng)++)
        {
            if (dest->mantissa_lng >= MAX_MANTISSA_LNG)
            {
                printf("\n\nПревышена допустимая длина строки");
                return ERR_INVALID_FLOAT_FORMAT;
            }

            dest->digits[dest->mantissa_lng] = str[pos] - ZERO_ASCII_CODE;
        }
    }

    if (str[pos] == 'e' || str[pos] == 'E')
    {
        int exp_sign;

        pos++;
        set_sign(str, &pos, &exp_sign);

        for (; isdigit((unsigned char)str[pos]); pos++)
            dest->exp_value = dest->exp_value * 10 + str[pos] - ZERO_ASCII_CODE;

        dest->exp_value *= exp_sign;
    }

    if (dest->exp_value > MAX_EXP_VALUE || dest->exp_value < MIN_EXP_VALUE)
    {
        printf("\n\nНедопутимое значение порядка");
        return ERR_EXP_VALUE;
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

int add_mantissas(const int *first, const int *second, int *result)
{
    int trans = 0;

    for (int i = MAX_MANTISSA_LNG - 1; i >= 0; i--)
    {
        int part_sum = first[i] + second[i] + trans;

        if (part_sum >= 10)
        {
            trans = 1;
            part_sum -= 10;
        }
        else
            trans = 0;

        result[i] = part_sum;
    }

    return EXIT_SUCCESS;
}

int mantissa_cmp(const int *first, const int *second)
{
    for (int i = 0; i < MAX_MANTISSA_LNG; i++)
        if (first[i] != second[i])
            return first[i] - second[i];

    return 0;
}

void arr_cpy(const int *src, int *dest, const int sz)
{
    for (int i = 0; i < sz; i++)
        dest[i] = src[i];
}

int subtract_mantissas(const int *fir, const int *sec, int *result)
{
    int first[MAX_MANTISSA_LNG], second[MAX_MANTISSA_LNG];
    arr_cpy(fir, first, MAX_MANTISSA_LNG);
    arr_cpy(sec, second, MAX_MANTISSA_LNG);

    for (int i = 0; i < MAX_MANTISSA_LNG; i++)
        result[i] = 0;

    for (int i = MAX_MANTISSA_LNG - 1; i >= 0; i--)
    {
        int part_diff = first[i] - second[i];

        if (part_diff < 0)
        {
            first[i - 1]--;
            part_diff = 10 + first[i] - second[i];
        }

        result[i] = part_diff;
    }

    return EXIT_SUCCESS;
}

int round_big_float_t(big_float_t *elem)
{
    if (elem->mantissa_lng == MAX_MANTISSA_LNG)
        for (int i = MAX_MANTISSA_LNG - 1; i >= 0; i--)
        {
            elem->digits[i]++;

            if (elem->digits[i] < 10)
                break;

            elem->digits[i] = 0;
            elem->mantissa_lng--;
        }

    return 1;
}


int divide_big_float(const big_float_t dividend, const big_float_t divider,
big_float_t *result)
{
    // exp
    result->exp_value = dividend.exp_value - divider.exp_value;
    result->sign = dividend.sign * divider.sign;

    // copy to pass const
    int dividend_digits[MAX_MANTISSA_LNG] = { 0 };
    arr_cpy(dividend.digits, dividend_digits, MAX_MANTISSA_LNG);
    int divider_digits[MAX_MANTISSA_LNG] = { 0 };
    arr_cpy(divider.digits, divider_digits, MAX_MANTISSA_LNG);

    // to store new value
    int result_digits[MAX_MANTISSA_LNG] = { 0 };
    int result_pos = 0;

    for (; result_pos < MAX_MANTISSA_LNG; result_pos++)
    {
        int cur_mantissa[MAX_MANTISSA_LNG] = { 0 };
        int cur_factor = 0;
        int cmp;
        add_mantissas(cur_mantissa, divider_digits, cur_mantissa);

        while ((cmp = mantissa_cmp(dividend_digits, cur_mantissa)) > 0)
        {
            add_mantissas(cur_mantissa, divider_digits, cur_mantissa);
            cur_factor++;
        }

        // to make factor 1 less
        subtract_mantissas(cur_mantissa, divider_digits, cur_mantissa);
        subtract_mantissas(dividend_digits, cur_mantissa, dividend_digits);
        result_digits[result_pos] = cur_factor;

        if (cmp == 0)
        {
            result_digits[result_pos]++;
            break;
        }

        if (dividend_digits[0] == 0)
            shift_arr_left(dividend_digits, 0, MAX_MANTISSA_LNG);
        else
            exit(10);
    }

    arr_cpy(result_digits, result->digits, MAX_MANTISSA_LNG);

    for (int i = MAX_MANTISSA_LNG - 1; i >= 0; i--)
        if (result_digits[i] != 0)
        {
            result->mantissa_lng = i + 1;
            break;
        }

    if (mantissa_cmp(dividend_digits, divider_digits) != 0)
    {
        int round_check_mantissa[MAX_MANTISSA_LNG] = { 0 };

        for (int i = 0; i < 5; i++)
            add_mantissas(divider_digits, round_check_mantissa,
                          round_check_mantissa);

        if (mantissa_cmp(dividend_digits, round_check_mantissa) > 0)
            round_big_float_t(result);
    }

    trim(result);

    if (result->exp_value < MIN_EXP_VALUE || result->exp_value > MAX_EXP_VALUE)
    {
        printf("Значение порядка результата превышает допутимые границы");
        return ERR_DIVISION_EXP_VALUE;
    }

    return EXIT_SUCCESS;
}

void print_float_input_info()
{
    printf("                                      \t"
           "----|----|----|----|----|----|\n");
    printf("Введите вещественное число (делитель):\t");
}

void print_int_input_info()
{
    printf("                                      \t"
           "----|----|----|----|----|----|\n");
    printf("Введите целое число (делимое):        \t");
}

int input_big_float(big_float_t *dest, const int check_int)
{
    char input[MAX_IN_STR_LNG + 1];

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1; // ?

    if (input[strlen(input) - 1] != '\n')
    {
        printf("\n\nПревышена допустимая длина строки");
        return ERR_STRING_TOO_LONG;
    }

    input[strlen(input) - 1] = '\0';

    if (strlen(input) == 0)
    {
        printf("\n\nПустой ввод");
        return ERR_EMPTY_STR;
    }

    int error;

    if (check_int)
        if (!is_int(input))
        {
            printf("\n\nВвденное число не соответствует формату целого числа.");
            return ERR_INVALID_INT_FORMAT;
        }

    if ((error = str_to_big_float_t(dest, input)) != OK)
        return error;

    return EXIT_SUCCESS;
}

int input_numbers(big_float_t *dividend, big_float_t *divider)
{
    int error;
    print_int_input_info();

    if ((error = input_big_float(dividend, 1)) != EXIT_SUCCESS)
        return error;

    print_float_input_info();

    if ((error = input_big_float(divider, 0)) != EXIT_SUCCESS)
        return error;

    if (is_zero(*divider))
    {
        printf("\n\nДеление на ноль");
        return ERR_DIVISION_BY_ZERO;
    }

    printf("\n\n");

    return EXIT_SUCCESS;
}

void print_result(const big_float_t dividend, const big_float_t divider, const
big_float_t result)
{
    printf("Делимое:\t");
    print_big_float(dividend);
    printf("Делитель:\t");
    print_big_float(divider);
    printf("Результат:\t");
    print_big_float(result);
}
