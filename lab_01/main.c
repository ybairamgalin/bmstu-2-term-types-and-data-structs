#include <stdio.h>
#include "string.h"
#include "errors.h"
#include "big_int.h"
#include "big_float.h"

int main()
{
    setbuf(stdout, NULL);

    char input[MAX_IN_STR_LNG + 1];

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    if (input[strlen(input) - 1] != '\n')
        return ERR_STRING_TOO_LONG;

    input[strlen(input) - 1] = '\0';

    big_float_t value;

    int error;

    if ((error = str_to_big_float_t(&value, input)) != OK)
        return error;

    print_big_float(value);

    return OK;
}