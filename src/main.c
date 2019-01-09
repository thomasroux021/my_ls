/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
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
    if (dest == NULL)
        return (NULL);
    for (k = 0; k < i; k += 1)
        dest[k] = str[k];
    for (m = 0; k + m < i + j; m += 1)
        dest[k + m] = src[m];
    dest[k + m] = '\0';
    return (dest);
}

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

    if (param == NULL)
        exit(84);
    param->l_ = 0;
    param->rec_ = 0;
    param->d_ = 0;
    param->r_ = 0;
    param->t_ = 0;
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

char **pars_file(int ac, char **av, t_param *param)
{
    int k = 0;
    int j = 0;
    char **dest;

    for (int i = 1; i < ac; i += 1) {
        (av[i][0] == '-' && k)?exit(84):0;
        k += (av[i][0] != '-')?1:0;
    }
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
        j += (i == 4)?1:0;
        dest[i] = time[i + j];
        i += 1;
    }
    return (dest);
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

void ls_l(struct dirent *lec, t_ls *ls, t_param *param)
{
    struct stat fs;
    struct passwd *usr;
    struct group *gr;
    char *type = "pcdb-ls";

    (stat(my_realloc(ls->adress, lec->d_name), &fs) == -1)?exit(84):0;
    usr = getpwuid(fs.st_uid);
    gr = getgrgid(fs.st_gid);
    ls->blocks = fs.st_blocks;
    (S_ISDIR(fs.st_mode) && param->rec_)?param->file =
    char_realloc(my_realloc(ls->adress, lec->d_name), param->file, param):0;
    ls->is_dir = type[(fs.st_mode & S_IFMT) >> 13];
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
    ls->date = my_time(ctime(&fs.st_mtim.tv_sec));
    ls->time = (int) fs.st_mtim.tv_sec;
}

void print_ls(t_param *param, t_ls **all_stat, int j)
{
    int start = (param->r_)?(param->f_size - 1):0;
    int end = (param->r_)?-1:(param->f_size + j);

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

void my_ls(char *file, t_param *param)
{
    struct dirent *lec;
    DIR *rep = opendir(file);
    int i = 0;
    int j = 0;
    t_ls **all_stat;
    t_ls *ls = malloc(sizeof(t_ls));

    param->blocks = 0;
    (rep == NULL || ls == NULL || readdir(rep) == NULL)?exit(84):0;
    while ((lec = readdir(rep)))
        i += (lec->d_name[0] != '.')?1:0;
    param->f_size = i;
    all_stat = malloc(sizeof(t_ls *) * (i + 1));
    closedir(rep);
    rep = opendir(file);
    (rep == NULL)?exit(84):0;
    while ((lec = readdir(rep))) {
        (ls == NULL || all_stat == NULL || lec == NULL)?exit(84):0;
        if (lec->d_name[0] != '.') {
            ls->adress = ((file[my_strlen(file) - 1] != '/'))?my_realloc(file,
                    "/"):file;
            ls_l(lec, ls, param);
            ls->name = lec->d_name;
            param->blocks += ls->blocks;
            all_stat[j] = ls;
            j += 1;
            ls = malloc(sizeof(t_ls));
        }
    }
    (param->t_)?all_stat = sort_int(param, all_stat):0;
    print_ls(param, all_stat, (!my_strcmp(file, "."))?0:1);
    closedir(rep);
}

int file_is_dir(char *file, t_param *param)
{
    t_ls *ls = malloc(sizeof(t_ls));
    struct stat fs;
    struct passwd *usr;
    struct group *gr;
    char *type = "pcdb-ls";

    (stat(file, &fs) == -1 || ls == NULL)?exit(84):0;
    usr = getpwuid(fs.st_uid);
    gr = getgrgid(fs.st_gid);
    ls->blocks = fs.st_blocks;
    if (S_ISDIR(fs.st_mode) && !param->d_)
        return (1);
    else
        ls->is_dir = type[(fs.st_mode & S_IFMT) >> 13];
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
    ls->date = my_time(ctime(&fs.st_mtim.tv_sec));
    ls->time = (int) fs.st_mtim.tv_sec;
    if (param->l_)
        my_printf("%c%c%c%c%c%c%c%c%c%c %d %s %s %d %s ", ls->is_dir, ls->r_usr,
            ls->w_usr, ls->x_usr, ls->r_grp, ls->w_grp, ls->x_grp, ls->r_oth,
            ls->w_oth, ls->x_oth, ls->nlink, ls->usr_name, ls->grp_name,
            ls->size, ls->date);
    my_printf("%s\n", file);
    return (0);
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
