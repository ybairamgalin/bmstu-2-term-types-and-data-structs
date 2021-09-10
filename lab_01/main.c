#include <stdio.h>
#include "string.h"
#include "errors.h"
#include "big_int.h"

int main()
{
    setbuf(stdout, NULL);

    char input[MAX_IN_STR_LNG + 1];

    if (fgets(input, sizeof(input), stdin) == NULL)
        return 1;

    if (input[strlen(input) - 1] != '\n')
        return ERR_STRING_TOO_LONG;

    input[strlen(input) - 1] = '\0';

    int error;
    big_int_t value;

    if ((error = str_to_big_int_t(&value, input)) != OK)
        return error;

    print_big_int(value);
    big_int_t_to_str(input, value);
    printf("%s", input);

    return OK;
}