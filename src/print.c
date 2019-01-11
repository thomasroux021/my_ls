/*
** EPITECH PROJECT, 2019
** print.c
** File description:
** print
*/

#include "my.h"

void print_ls(t_param *param, t_ls **all_stat)
{
    int start = (param->r_)?(param->f_size - 1):0;
    int end = (param->r_)?-1:(param->f_size);

    (param->l_)?my_printf("total %d\n", param->blocks / 2):0;
    while (start != end) {
        if (param->l_)
            print_l(all_stat[param->pos_size], all_stat[start]);
        my_printf("%s\n", all_stat[start]->name);
        start += (end - start < 0)?-1:1;
    }
}

void print_l(t_ls *stat_end, t_ls *stat_start)
{
    char *space1 = my_space(stat_end->s1 - len_nbr(stat_start->nlink));
    char *space2 = my_space(stat_end->s2 - my_strlen(stat_start->usr_name));
    char *space3 = my_space(stat_end->s3 - my_strlen(stat_start->grp_name));
    char *space4 = my_space(stat_end->s4 - len_nbr(stat_start->size));

    my_printf("%c%c%c%c%c%c%c%c%c%c %s%d %s%s %s%s %s%d %s ", stat_start->
        is_dir, stat_start->r_usr, stat_start->w_usr, stat_start->x_usr,
        stat_start->r_grp, stat_start->w_grp, stat_start->x_grp, stat_start->
        r_oth, stat_start->w_oth, stat_start->x_oth, space1, stat_start->nlink,
        stat_start->usr_name, space2, stat_start->grp_name, space3, space4,
        stat_start->size, stat_start->date);
    free(space1);
    free(space2);
    free(space3);
    free(space4);
}

char *my_space(int nb)
{
    char *dest = malloc(sizeof(char) * (nb + 1));
    int i;

    (dest == NULL)?exit(84):0;
    for (i = 0; i < nb; i += 1)
        dest[i] = ' ';
    dest[i] = '\0';
    return (dest);
}

char *my_time(char *time)
{
    char *dest;
    int i;
    int j = 4;
    int ddot = 0;

    for (i = 0; time[i]; i += 1);
    dest = malloc(sizeof(char) * i);
    (dest == NULL)?exit(84):0;
    i = 0;
    while (time[i + j]) {
        ddot += (time[i + j] == ':')?1:0;
        if (ddot == 2) {
            dest[i] = '\0';
            break;
        }
        dest[i] = time[i + j];
        i += 1;
    }
    return (dest);
}
