/*
** EPITECH PROJECT, 2018
** my_pointer.c
** File description:
** manage unsigned and pointer
*/

#include "my.h"

void unsign(unsigned int i, int base, int maj)
{
    if (base == 10) {
        if (i < 0)
            my_put_nbr(i + 4294967296);
        else
            my_put_nbr(i);
    } else {
        if (i < 0)
            decitobase(i + 4294967296, base, maj);
        else
            decitobase(i, base, maj);
    }
}

void pointer(long x)
{
    char hexa[] = "0123456789abcdef";
    int i = 44;
    int zero = 0;

    while (i >= 0) {
        if (hexa[x >> i & 15] != '0' || zero) {
            my_putchar(hexa[x >> i & 15]);
            zero += 1;
        }
        i -= 4;
    }
}
