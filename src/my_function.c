/*
** EPITECH PROJECT, 2018
** my_function.c
** File description:
** some function
*/

#include "my.h"
#include <stdarg.h>
#include <stdlib.h>

char *fill(char *result, int len)
{
    int i = 0;

    while (i < len) {
        result[i] = '0';
        i += 1;
    }
    result[len] = '\0';
    return (result);
}

char *clean_zero(char *result)
{
    int i = 0;
    char *str = malloc(sizeof(char) * (my_strlen(result) + 1));

    while (*result == '0' && *(result + 1) != '\0')
        result++;
    while (*result != '\0') {
        str[i] = *result;
        i += 1;
        result++;
    }
    str[i] = '\0';
    return (str);
}

char *chartostr(char c)
{
    char *str = my_strdup(" ");

    str[0] = c;
    return (str);
}

char *octal(char c)
{
    char *mem = my_strdup("\\000");
    int r = c;

    mem[3] = r % 8 + 48;
    mem[2] = r / 8 % 8 + 48;
    mem[1] = r / 64 % 8 + 48;
    return (mem);
}

void decitobase(long i, int base, int maj)
{
    linked_list_t *result = NULL;

    while (i != 0) {
        if (i % base <= 9)
            add_element_at_begin(&result, chartostr(i % base + 48));
        if (i % base > 9 && !maj)
            add_element_at_begin(&result, chartostr(i % base + 87));
        if (i % base > 9 && maj)
            add_element_at_begin(&result, chartostr(i % base + 55));
        i = i / base;
    }
    my_putstr(my_revstr(my_linkedtostr(result)));
}
