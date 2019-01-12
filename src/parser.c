/*
** EPITECH PROJECT, 2019
** parser.c
** File description:
** parser
*/

#include "my.h"

char *my_realloc(char *str, char *src)
{
    int i;
    int j;
    int k;
    int m;
    char *dest;

    for (i = 0; str[i] != '\0'; i += 1);
    for (j = 0; src[j] != '\0'; j += 1);
    dest = malloc(sizeof(char) * (i + j + 1));
    (dest == NULL)?exit(84):0;
    for (k = 0; k < i; k += 1)
        dest[k] = str[k];
    for (m = 0; k + m < i + j; m += 1)
        dest[k + m] = src[m];
    dest[k + m] = '\0';
    return (dest);
}

void define_param(t_param *param)
{
    param->l_ = 0;
    param->rec_ = 0;
    param->d_ = 0;
    param->r_ = 0;
    param->t_ = 0;
}

t_param *my_param(int ac, char **av)
{
    t_param *param = malloc(sizeof(t_param));
    int j = 1;

    (param == NULL)?exit(84):0;
    define_param(param);
    for (int i = 1; i < ac; i += 1) {
        (av[i][0] == '-' && av[i][1] == '\0')?exit(84):0;
        while (av[i][0] == '-' && av[i][j]) {
            (av[i][j] != 'l' && av[i][j] != 'R' && av[i][j] != 'd' &&
            av[i][j] != 'r' && av[i][j] != 't')?exit(84):0;
            param->l_ = (av[i][j] == 'l')?1:param->l_;
            param->rec_ = (av[i][j] == 'R')?1:param->rec_;
            param->d_ = (av[i][j] == 'd')?1:param->d_;
            param->r_ = (av[i][j] == 'r')?1:param->r_;
            param->t_ = (av[i][j] == 't')?1:param->t_;
            j += 1;
        }
        j = 1;
    }
    return (param);
}

int nb_file(int ac, char **av)
{
    int k = 0;

    for (int i = 1; i < ac; i += 1)
        k += (av[i][0] != '-')?1:0;
    return (k);
}

char **pars_file(int ac, char **av, t_param *param)
{
    int k = nb_file(ac, av);
    int j = 0;
    char **dest;

    param->n_arg = k;
    dest = malloc(sizeof(char *) * (k + 2));
    (dest == NULL)?exit(84):0;
    if (!k) {
        dest[0] = ".";
        dest[1] = "-end";
        return (dest);
    }
    for (int i = 1; i < ac; i += 1) {
        if (av[i][0] != '-') {
            dest[j] = av[i];
            j += 1;
        }
    }
    dest[j] = "-end";
    return (dest);
}
