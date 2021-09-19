#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include "big_int.h"
#include "errors.h"

int is_int(const char *str)
{
    regex_t int_regex;

    if ((regcomp(&int_regex, INT_REGEX, REG_EXTENDED)) != OK)
        exit(ERR_REGEX_COMP);

    if (regexec(&int_regex, str, 0, NULL, 0) != OK)
        return 0;

    return 1;
}

int str_to_big_int_t(big_int_t *dest, const char *str)
{
    if (!is_int(str))
        return ERR_INVALID_INT_FORMAT;

    int pos = 0;

    if (str[0] == '+')
    {
        dest->sign = 1;
        pos++;
    }
    else if (str[0] == '-')
    {
        dest->sign = -1;
        pos++;
    }
    else
        dest->sign = 1;

    for (int i = 0; pos < strlen(str); i++, pos++)
    {
        if (pos > MAX_MANTISSA_LNG)
            return ERR_INT_TOO_LONG;

        dest->digits[i] = str[pos] - ZERO_ASCII_CODE;
        dest->mantissa_lng = i + 1;
    }

    return OK;
}

void print_big_int(const big_int_t elem)
{
    if (elem.sign == -1)
        printf("-");

    for (int i = 0; i < elem.mantissa_lng; i++)
        printf("%d", elem.digits[i]);

    printf("\n");
}

void big_int_t_to_str(char *dest, const big_int_t src)
{
    int pos = 0;

    if (src.sign == -1)
        dest[pos++] = '-';

    for (int i = 0; i < src.mantissa_lng; i++, pos++)
        dest[pos] = src.digits[i] + ZERO_ASCII_CODE;

    dest[pos] = '\0';
}