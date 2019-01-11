/*
** EPITECH PROJECT, 2019
** file.c
** File description:
** file
*/

#include "my.h"

void param_file(t_ls *ls, struct stat fs)
{
    struct passwd *usr;
    struct group *gr;

    usr = getpwuid(fs.st_uid);
    gr = getgrgid(fs.st_gid);
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

int file_is_dir(char *file, t_param *param)
{
    t_ls *ls = malloc(sizeof(t_ls));
    struct stat fs;
    char *type = "pcdb-ls";

    (stat(file, &fs) == -1 || ls == NULL)?exit(84):0;
    ls->blocks = fs.st_blocks;
    if (S_ISDIR(fs.st_mode) && !param->d_)
        return (1);
    else
        ls->is_dir = type[(fs.st_mode & S_IFMT) >> 13];
    param_file(ls, fs);
    if (param->l_)
        my_printf("%c%c%c%c%c%c%c%c%c%c %d %s %s %d %s ", ls->is_dir, ls->r_usr,
            ls->w_usr, ls->x_usr, ls->r_grp, ls->w_grp, ls->x_grp, ls->r_oth,
            ls->w_oth, ls->x_oth, ls->nlink, ls->usr_name, ls->grp_name,
            ls->size, ls->date);
    my_printf("%s\n", file);
    return (0);
}
