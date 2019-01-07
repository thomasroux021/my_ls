/*
** EPITECH PROJECT, 2018
** disp_stdarg.c
** File description:
** disp
*/

#include "my.h"
#include <stdarg.h>

int disp_stdarg(char *s, ...)
{
    va_list list;
    int i = 0;

    va_start(list, s);
    while (s[i] != '\0') {
        if (s[i] == 'c')
            my_putchar(va_arg(list, int));
        if (s[i] == 's')
            my_putstr(va_arg(list, char *));
        if (s[i] == 'i')
            my_put_nbr(va_arg(list, int));
        i += 1;
        my_putchar('\n');
    }
    va_end(list);
}
