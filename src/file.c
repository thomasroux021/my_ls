/*
** EPITECH PROJECT, 2019
** file.c
** File description:
** file
*/

#include "my.h"

void param_file(t_ls *ls, struct stat fs, char *file)
{
    struct passwd *usr = getpwuid(fs.st_uid);
    struct group *gr = getgrgid(fs.st_gid);
    char *mem = ctime(&fs.st_mtim.tv_sec);
    char *buf = malloc(sizeof(char) * 100);
    ssize_t size;

    (usr == NULL || gr == NULL || mem == NULL || buf == NULL)?exit(84):0;
    if (ls->is_dir == 'l')
        ((size = readlink(file, buf, (size_t) 100)) == -1)?
        exit(84):(buf[size] = '\0');
    sticky(ls, fs);
    ls->name = (ls->is_dir == 'l')?my_realloc(my_realloc(file, " -> "),
            buf):file;
    ls->nlink = fs.st_nlink;
    ls->usr_name = usr->pw_name;
    ls->grp_name = gr->gr_name;
    ls->size = fs.st_size;
    ls->date = my_time(mem);
    ls->time = (int) fs.st_mtim.tv_sec;
}

int file_is_dir(char *file, t_param *param)
{
    t_ls *ls = malloc(sizeof(t_ls));
    struct stat fs;
    char *type = "pcdb-ls";

    (lstat(file, &fs) == -1 || ls == NULL)?exit(84):0;
    ls->blocks = fs.st_blocks;
    if (S_ISDIR(fs.st_mode) && !param->d_)
        return (1);
    else
        ls->is_dir = type[(fs.st_mode & S_IFMT) >> 13];
    param_file(ls, fs, file);
    if (param->l_)
        my_printf("%c%c%c%c%c%c%c%c%c%c %d %s %s %d %s ", ls->is_dir, ls->r_usr,
            ls->w_usr, ls->x_usr, ls->r_grp, ls->w_grp, ls->x_grp, ls->r_oth,
            ls->w_oth, ls->x_oth, ls->nlink, ls->usr_name, ls->grp_name,
            ls->size, ls->date);
    my_printf("%s\n", ls->name);
    return (0);
}
