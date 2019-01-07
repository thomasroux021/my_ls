/*
** EPITECH PROJECT, 2018
** my_printf.c
** File description:
** printf
*/

#include "my.h"
#include <stdarg.h>
#include <stdlib.h>

char *parser(char *str)
{
    int i = 0;
    linked_list_t *dest = NULL;

    while (str[i] != '\0') {
        if (str[i] >= 32 && str[i] < 127)
            add_element_at_begin(&dest, chartostr(str[i]));
        else
            add_element_at_begin(&dest, octal(str[i]));
        i += 1;
    }
    return (my_linkedtostr(dest));
}

int charisflag(char c)
{
    if (c == 's' || c == 'S' || c == 'x' || c == 'X' || c == 'd' || c == 'b' ||
        c == 'u' || c == 'i' || c == 'p' || c == 'c' || c == '#' ||
        c == '+')
        return (1);
    if (c == '%')
        return (2);
    return (0);
}

void flag3(char *str, int i, va_list list)
{
    if (str[i] == 'p') {
        my_putstr("0x");
        pointer(va_arg(list, void *));
    }
    if (str[i + 1] != '\0' && str[i] == ' ')
        flag1(str, i + 1, list);
}

void signe(int i)
{
    if (i >= 0)
        my_putchar('+');
    my_put_nbr(i);
}

int my_printf(char *str, ...)
{
    va_list list;
    int i = 0;
    int pur = 0;

    va_start(list, str);
    while (str[i] != '\0') {
        if (str[i + 1] != '\0' && str[i + 1] == '%' && str[i] == '%' && !pur)
            pur = 1;
        else if (str[i + 1] != '\0' && str[i + 1] == '%' && str[i]
                == '%' && pur)
            pur = 0;
        if (str[i] == '%' && !pur)
            flag1(str, i + 1, list);
        else if (!charisflag(str[i]) || ((!i || pur) &&
                charisflag(str[i]) == 1) || (str[i] == '%' &&
                charisflag(str[i + 1]) != 1 && pur))
            my_putchar(str[i]);
        i += 1;
    }
    va_end(list);
}
