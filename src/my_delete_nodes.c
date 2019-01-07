/*
** EPITECH PROJECT, 2018
** my_find_node
** File description:
** delete nodes of list
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"
#include <string.h>
#include <stdio.h>

void destroye_linked_list_t(linked_list_t *element)
{
    free(element);
}

void delete_link(linked_list_t **begin, linked_list_t *element)
{
    linked_list_t *last = *begin;

    if (element == *begin) {
        *begin = element->next;
        destroye_linked_list_t(element);
        return;
    }
    while (last->next != NULL) {
        if (last->next == element) {
            last->next = last->next->next;
            destroye_linked_list_t(element);
        } else
            last = last->next;
    }
}

int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)())
{
    linked_list_t *temp;

    temp = *begin;
    while (temp != NULL) {
        if (!(*cmp)(temp->data, data_ref))
            delete_link(begin, temp);
        temp = temp->next;
    }
}
