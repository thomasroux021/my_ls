/*
** EPITECH PROJECT, 2018
** my_rev_list
** File description:
** rev linked list
*/

#include <stdlib.h>
#include <stddef.h>
#include "my.h"

void my_rev_list(linked_list_t **begin)
{
    linked_list_t *last = NULL;
    linked_list_t *temp;
    linked_list_t *next;
    if ((*begin) != NULL && (*begin)->next != NULL) {
        temp = *begin;
        next = temp->next;
        while (next != NULL) {
            temp->next = last;
            last = temp;
            temp = next;
            next = next->next;
        }
        temp->next = last;
        *begin = temp;
    }
}
