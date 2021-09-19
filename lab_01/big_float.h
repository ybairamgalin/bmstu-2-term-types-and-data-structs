#ifndef _BIG_FLOAT_H_
#define _BIG_FLOAT_H_

#define MAX_MANTISSA_LNG 30
#define MAX_IN_STR_LNG MAX_MANTISSA_LNG + 3

#define ZERO_ASCII_CODE 48

#define FLOAT_REGEX "^[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)$"

typedef struct
{
    int sign;
    int digits[MAX_MANTISSA_LNG];
    size_t mantissa_lng;
    int exp_value;
} big_float_t;

int str_to_big_float_t(big_float_t *dest, const char *str);
void big_float_t_to_str(char *dest, const big_float_t src);
void print_big_float(const big_float_t elem);

#endif
