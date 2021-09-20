#ifndef _BIG_FLOAT_H_
#define _BIG_FLOAT_H_

#define MAX_MANTISSA_LNG 30
#define MAX_IN_STR_LNG MAX_MANTISSA_LNG + 3

#define MAX_EXP_VALUE 99999
#define MIN_EXP_VALUE -99999

#define ERR_DIVISION_EXP_VALUE 1
#define ERR_EMPTY_STR -1
#define ERR_DIVISION_BY_ZERO -2
#define ERR_EXP_VALUE -3

#define ZERO_ASCII_CODE 48

#define FLOAT_REGEX "^[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)$"
#define INT_REGEX "^[+-]?([0-9]+([eE][+-]?[0-9]+)?)$"

typedef struct
{
    int sign;
    int digits[MAX_MANTISSA_LNG];
    size_t mantissa_lng;
    int exp_value;
} big_float_t;

void print_result(const big_float_t dividend, const big_float_t divider, const
big_float_t result);
int input_numbers(big_float_t *dividend, big_float_t *divider);
int input_big_float(big_float_t *dest, const int check_int);
void big_float_t_to_str(char *dest, const big_float_t src);
void print_big_float(const big_float_t elem);
int divide_big_float(const big_float_t dividend, const big_float_t divider,
                     big_float_t *result);
big_float_t empty();

#endif
