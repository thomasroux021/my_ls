/*
** EPITECH PROJECT, 2018
** my_params_to_list
** File description:
** add nodes to list
*/

#include <stddef.h>
#include <stdlib.h>
#include "my.h"

linked_list_t *add_element_at_begin(linked_list_t **list, char *data)
{
    linked_list_t *new_list;

    new_list = malloc(sizeof(*new_list));
    new_list->data = data;
    new_list->next = *list;
    *list = new_list;
    return (*list);
}

linked_list_t *my_params_to_list(int ac, char * const *av)
{
    int i = 0;
    linked_list_t *list = NULL;

    while (i < ac) {
        add_element_at_begin(&list, av[i]);
        i++;
    }
    return (list);
}
