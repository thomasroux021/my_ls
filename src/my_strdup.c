/*
** EPITECH PROJECT, 2018
** my_strdup.c
** File description:
** strdup
*/

#include "my.h"
#include <stdlib.h>

char *my_strdup(char const *str)
{
    char *r = malloc(sizeof(char) * (my_strlen(str) + 1));

    return (my_strcpy(r, str));
}
