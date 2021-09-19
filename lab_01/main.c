#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "errors.h"
#include "big_float.h"

int main(void)
{
    setbuf(stdout, NULL);

    int error;
    big_float_t dividend;

    if ((error = input_big_float(&dividend)) != EXIT_SUCCESS)
        return error;

    big_float_t divider = empty();

    if ((error = input_big_float(&divider)) != EXIT_SUCCESS)
        return error;

    big_float_t result = empty();

    divide_big_float(dividend, divider, &result);

    print_big_float(result);

    return OK;
}