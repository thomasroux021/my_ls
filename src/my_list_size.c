/*
** EPITECH PROJECT, 2018
** list_size
** File description:
** calcul list size
*/

#include "my.h"
#include <stddef.h>
#include <stdlib.h>

int my_list_size(linked_list_t const *begin)
{
    int i = 0;
    linked_list_t const *temp;

    temp = begin;
    while (temp != NULL) {
        i++;
        temp = temp->next;
    }
    return i;
}

int my_charlist_size(linked_list_t *list)
{
    int i = 0;
    linked_list_t const *temp;

    temp = list;
    while (temp != NULL) {
        i = i + my_strlen(temp->data);
        temp = temp->next;
    }
    return (i);
}

char *my_linkedtostr(linked_list_t *list)
{
    int j = 0;
    int i = 0;
    linked_list_t *temp = list;
    char *dest = malloc(sizeof(char) * (i + 1));

    (dest == NULL)?exit(84):0;
    fill(dest, my_charlist_size(list));
    while (dest[i] != '\0' && temp != NULL) {
        while (temp != NULL && (temp->data)[j] != '\0')
            j += 1;
        j -= 1;
        while (temp != NULL && j >= 0) {
            dest[i] = (temp->data)[j];
            j -= 1;
            i += 1;
        }
        j = 0;
        temp = temp->next;
    }
    return (clean_zero(my_revstr(dest)));
}
