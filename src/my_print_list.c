/*
** EPITECH PROJECT, 2018
** print_list
** File description:
** print list
*/

#include <stddef.h>
#include "my.h"
#include <stdlib.h>

void print_list(linked_list_t *s)
{
    while (s != NULL) {
        my_putstr(s->data);
        my_putchar('\n');
        s = s->next;
    }
}
