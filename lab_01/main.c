#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "big_float.h"

void print_program_info()
{
    printf("МГТУ им. Н.Э.Баумана | Байрамгалин Ярслав ИУ7-33Б\n\n"
           "В программе реализована операция деления целового числа на "
           "вещественное.\n\n"
           "Целое чисто может быть введено в обычной '123' форме.\n"
           "Вещественное число может быть "
           "введено как '.000256', '+123001', '123.456', '1324657e-20',"
           "'123e20','123.4567e23'.\n"
           "В программе реализована возможность "
           "представления вещественного числа в любом из перечисленных "
           "представлений.\n\n"
           "Для вещественных и целых чисел установлен "
           "следующий диапазон допустимых значений: длина мантиссы не может "
           "превышать 30 символов, порядок - целое число от"
           "-99999 до 99999\n\n");
}

int main(void)
{
    setbuf(stdout, NULL);

    int error;
    big_float_t dividend, divider;
    print_program_info();

    if ((error = input_numbers(&dividend, &divider)) != EXIT_SUCCESS)
        return error;

    big_float_t result = empty();

    if ((error = divide_big_float(dividend, divider, &result)) != EXIT_SUCCESS)
        return error;

    print_result(dividend, divider, result);

    return EXIT_SUCCESS;
}
