#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#define MAX_MANTISSA_LNG 30
#define MAX_IN_STR_LNG MAX_MANTISSA_LNG + 3

#define ZERO_ASCII_CODE 48

#define INT_REGEX "^[+-]?[1-9][0-9]{0,29}$"

typedef struct
{
    int sign;
    char digits[MAX_MANTISSA_LNG + 1];
} big_int_t;

int str_to_big_int_t(big_int_t *dest, const char *str);
void big_int_t_to_str(char *dest, const big_int_t src);
void print_big_int(const big_int_t elem);

#endif
