/*
** EPITECH PROJECT, 2018
** function.c
** File description:
** function
*/

#include "my.h"
#include <stdarg.h>
#include <stdlib.h>

void flag2(char *str, int i, va_list list)
{
    if (str[i] == 's')
        my_putstr(va_arg(list, char *));
    if (str[i] == 'b')
        unsign(va_arg(list, unsigned int), 2, 0);
    if (str[i] == 'x')
        unsign(va_arg(list, unsigned int), 16, 0);
    if (str[i] == 'X')
        unsign(va_arg(list, unsigned int), 16, 1);
    if (str[i + 1] != '\0' && str[i] == '#') {
        if (str[i + 1] == 'x')
            my_putstr("0x");
        if (str[i + 1] == 'X')
            my_putstr("0X");
        if (str[i + 1] == 'o')
            my_putchar('0');
        flag1(str, i + 1, list);
    }
    flag3(str, i, list);
}

void flag1(char *str, int i, va_list list)
{
    if (str[i] == 'S')
        my_putstr(parser(va_arg(list, char *)));
    if (str[i] == 'd' || str[i] == 'i')
        my_put_nbr(va_arg(list, int));
    if (str[i] == 'u')
        unsign(va_arg(list, unsigned int), 10, 0);
    if (str[i] == 'c')
        my_putchar(va_arg(list, int));
    if (str[i] == 'o')
        unsign(va_arg(list, unsigned int), 8, 0);
    if (str[i + 1] != '\0' && str[i] == '+') {
        if (str[i + 1] == 'd' || str[i + 1] == 'i')
            signe(va_arg(list, int));
        if (str[i + 1] == '+')
            flag1(str, i + 1, list);
    }
    flag2(str, i, list);
}
