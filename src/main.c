/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

t_ls **sort_int(t_param *param, t_ls **all_stat)
{
    t_ls *mem;
    int sort = 0;

    for (int i = 0; i < param->f_size; i += 1) {
        for (int j = 0; j < param->f_size - 1; j += 1) {
            sort = (all_stat[j]->time < all_stat[j + 1]->time)?1:0;
            (sort && j == param->pos_size - 1)?param->pos_size -= 1:0;
            (sort)?mem = all_stat[j]:0;
            (sort)?all_stat[j] = all_stat[j + 1]:0;
            (sort)?all_stat[j + 1] = mem:0;
            sort = 0;
        }
    }
    return (all_stat);
}

char **char_realloc(char *file, char **all_file, t_param *param)
{
    char **dest = malloc(sizeof(char *) * (param->n_arg + 3));
    int i;
    int j = 0;

    (dest == NULL)?exit(84):0;
    param->n_arg += 1;
    for (i = 0; my_strcmp(all_file[i], "-end"); i += 1) {
        if (param->i + 1 == i) {
            dest[i] = file;
            j += 1;
        } else
            dest[i + j] = all_file[i];
    }
    if (param->i + 1 == i) {
        dest[i] = file;
        j += 1;
    }
    dest[i + j] = "-end";
    param->i += 1;
    return (dest);
}

void change_size(t_ls *ls, t_ls **all_stat, int j)
{
    (j && ls->s1 < all_stat[j - 1]->s1)?ls->s1 = all_stat[j - 1]->s1:0;
    (j && ls->s2 < all_stat[j - 1]->s2)?ls->s2 = all_stat[j - 1]->s2:0;
    (j && ls->s3 < all_stat[j - 1]->s3)?ls->s3 = all_stat[j - 1]->s3:0;
    (j && ls->s4 < all_stat[j - 1]->s4)?ls->s4 = all_stat[j - 1]->s4:0;
}

void fill_stat(char *file, t_param *param, t_ls **all_stat, t_ls *ls)
{
    DIR *rep = opendir(file);
    struct dirent *lec;
    int j = 0;

    (rep == NULL)?exit(84):0;
    param->pos_size = param->f_size - 1;
    while ((lec = readdir(rep))) {
        (ls == NULL || all_stat == NULL || lec == NULL)?exit(84):0;
        if (lec->d_name[0] != '.') {
            ls_l(lec, ls, param, file);
            param->blocks += ls->blocks;
            change_size(ls, all_stat, j);
            all_stat[j] = ls;
            j += 1;
            ls = malloc(sizeof(t_ls));
        }
    }
    (param->t_)?all_stat = sort_int(param, all_stat):0;
    print_ls(param, all_stat);
    (closedir(rep) == -1)?exit(84):0;
}

int main(int ac, char **av)
{
    t_param *param = my_param(ac, av);
    char **file = pars_file(ac, av, param);
    int i = 0;

    param->i = 0;
    param->file = file;
    while (my_strcmp(param->file[i], "-end")) {
        if (file_is_dir(param->file[i], param)) {
            (param->n_arg > 1 && i)?my_putchar('\n'):0;
            (param->n_arg > 1 || param->rec_)?
                my_printf("%s:\n", param->file[i]):0;
            my_ls(param->file[i], param);
        }
        param->i += (param->i == i)?1:0;
        i += 1;
    }
}
