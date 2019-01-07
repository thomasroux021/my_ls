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
            (sort)?mem = all_stat[j]:0;
            (sort)?all_stat[j] = all_stat[j + 1]:0;
            (sort)?all_stat[j + 1] = mem:0;
            sort = 0;
        }
    }
    return (all_stat);
}

t_param *my_param(int ac, char **av)
{
    t_param *param = malloc(sizeof(t_param));
    int j = 1;

    param->l_ = 0;
    param->rec_ = 0;
    param->d_ = 0;
    param->r_ = 0;
    param->t_ = 0;
    param->blocks = 0;
    if (param == NULL)
        exit(84);
    for (int i = 1; i < ac; i += 1) {
        if (av[i][0] != '-')
            break;
        while (av[i][j]) {
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

char *pars_file(int ac, char **av)
{
    return (".");
}

char *my_time(char *time)
{
    char *dest;
    int i;
    int j = 4;
    int ddot = 0;

    for (i = 0; time[i]; i += 1);
    dest = malloc(sizeof(char) * i);
    i = 0;
    while (time[i + j]) {
        if (time[i + j] == ':')
            ddot += 1;
        if (ddot == 2) {
            dest[i] = '\0';
            break;
        }
        j += (i == 4)?1:0;
        dest[i] = time[i + j];
        i += 1;
    }
    return (dest);
}

void ls_l(int ac, char **av, struct dirent *lec, t_ls *ls)
{
    struct stat fs;
    struct passwd *usr;
    struct group *gr;

    stat(lec->d_name, &fs);
    usr = getpwuid(fs.st_uid);
    gr = getgrgid(fs.st_gid);
    ls->blocks = fs.st_blocks;
    ls->is_dir = (S_ISDIR(fs.st_mode))?'d':'-';
    ls->r_usr = (fs.st_mode & S_IRUSR)?'r':'-';
    ls->w_usr = (fs.st_mode & S_IWUSR)?'w':'-';
    ls->x_usr = (fs.st_mode & S_IXUSR)?'x':'-';
    ls->r_grp = (fs.st_mode & S_IRGRP)?'r':'-';
    ls->w_grp = (fs.st_mode & S_IWGRP)?'w':'-';
    ls->x_grp = (fs.st_mode & S_IXGRP)?'x':'-';
    ls->r_oth = (fs.st_mode & S_IROTH)?'r':'-';
    ls->w_oth = (fs.st_mode & S_IWOTH)?'w':'-';
    ls->x_oth = (fs.st_mode & S_IXOTH)?'x':'-';
    ls->nlink = fs.st_nlink;
    ls->usr_name = usr->pw_name;
    ls->grp_name = gr->gr_name;
    ls->size = fs.st_size;
    ls->date = my_time(ctime(&fs.st_mtim));
    ls->time = (int) fs.st_mtim.tv_sec;
}

void print_ls(t_param *param, t_ls **all_stat)
{
    int start = (param->r_)?(param->f_size - 1):0;
    int end = (param->r_)?-1:(param->f_size);

    (param->l_)?my_printf("total %d\n", param->blocks / 2):0;
    while (start != end) {
        if (param->l_) {
            my_printf("%c%c%c%c%c%c%c%c%c%c %d %s %s %d %s ", all_stat[start]->
            is_dir, all_stat[start]->r_usr, all_stat[start]->w_usr,
            all_stat[start]->x_usr, all_stat[start]->r_grp, all_stat[start]->
            w_grp, all_stat[start]->x_grp, all_stat[start]->r_oth,
            all_stat[start]->w_oth, all_stat[start]->x_oth, all_stat[start]->
            nlink, all_stat[start]->usr_name, all_stat[start]->grp_name,
            all_stat[start]->size, all_stat[start]->date);
        }
        my_printf("%s\n", all_stat[start]->name);
        start += (end - start < 0)?-1:1;
    }
}

int main(int ac, char **av)
{
    char *file = pars_file(ac, av);
    struct dirent *lec;
    DIR *rep = opendir(file);
    int i = 0;
    int j = 0;
    t_param *param = my_param(ac, av);
    t_ls **all_stat;
    t_ls *ls = malloc(sizeof(t_ls));

    printf("%d\n", ac);
    if (rep == NULL)
        return (84);
    while ((lec = readdir(rep))) {
        if (lec->d_name[0] != '.')
            i += 1;
    }
    param->f_size = i;
    all_stat = malloc(sizeof(t_ls *) * i);
    closedir(rep);
    rep = opendir(file);
    while ((lec = readdir(rep))) {
        if (ls == NULL || all_stat == NULL)
            return (84);
        if (lec->d_name[0] != '.') {
            ls->adress = file;
            ls_l(ac, av, lec, ls);
            ls->name = lec->d_name;
            param->blocks += ls->blocks;
            all_stat[j] = ls;
            j += 1;
            ls = malloc(sizeof(t_ls));
        }
    }
    closedir(rep);
    (param->t_)?all_stat = sort_int(param, all_stat):0;
    print_ls(param, all_stat);
}
