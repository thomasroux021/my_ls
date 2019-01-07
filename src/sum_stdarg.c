/*
** EPITECH PROJECT, 2018
** sum_stdarg.c
** File description:
** sum
*/

#include "my.h"
#include <stdarg.h>

int sum_stdarg(int i, int nb, ...)
{
    int result = 0;
    va_list list;

    va_start(list, nb);
    if (!i) {
        while (nb != 0) {
            result += va_arg(list, int);
            nb -= 1;
        }
    } else {
        while (nb != 0) {
            result += my_strlen(va_arg(list, char *));
            nb -= 1;
        }
    }
    va_end(list);
    return (result);
}
