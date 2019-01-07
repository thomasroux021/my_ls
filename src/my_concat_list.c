/*
** EPITECH PROJECT, 2018
** my_concat_list
** File description:
** concat list
*/

#include <stddef.h>
#include "my.h"
#include <stdlib.h>

void my_concat_list(linked_list_t **begin, linked_list_t *begin2)
{
    linked_list_t *temp = *begin;
    if (temp != NULL) {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = begin2;
    } else {
        *begin = begin2;
    }
}
