/*
** EPITECH PROJECT, 2019
** my_ls
** File description:
** my_ls
*/

#include "my.h"

char *my_strtostr(char *src)
{
    char *dest = malloc(sizeof(char) * (my_strlen(src) + 1));
    int i;

    (dest == NULL)?exit(84):0;
    for (i = 0; src[i]; i += 1)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

int len_nbr(int nb)
{
    int len = 0;

    if (!nb)
        return (1);
    while (nb != 0) {
        nb = nb / 10;
        len += 1;
    }
    return (len);
}

void ls_l2(t_ls *ls, struct stat fs, struct dirent *lec)
{
    char *mem = ctime(&fs.st_mtim.tv_sec);
    char *buf = malloc(sizeof(char) * 100);
    ssize_t size;

    (mem == NULL || buf == NULL)?exit(84):0;
    if (ls->is_dir == 'l')
        ((size = readlink(my_realloc(ls->adress, lec->d_name), buf,
        (size_t) 100)) == -1)?exit(84):(buf[size] = '\0');
    (mem == NULL)?exit(84):0;
    ls->name = (ls->is_dir == 'l')?my_realloc(my_realloc(lec->d_name, " -> "),
            buf):(lec->d_name);
    sticky(ls, fs);
    ls->nlink = fs.st_nlink;
    ls->s1 = len_nbr((int) ls->nlink);
    ls->size = fs.st_size;
    ls->s4 = len_nbr((int) ls->size);
    ls->date = my_time(mem);
    ls->time = (int) fs.st_mtim.tv_sec;
    free(buf);
}

void ls_l(struct dirent *lec, t_ls *ls, t_param *param, char *file)
{
    struct stat fs;
    struct passwd *usr;
    struct group *gr;
    char *type = "pcdb-ls";

    ls->adress = ((file[my_strlen(file) - 1] != '/'))?my_realloc(file,
                    "/"):file;
    (lstat(my_realloc(ls->adress, lec->d_name), &fs) == -1)?exit(84):0;
    usr = getpwuid(fs.st_uid);
    gr = getgrgid(fs.st_gid);
    (usr == NULL || gr == NULL)?exit(84):0;
    ls->blocks = fs.st_blocks;
    ls->is_dir = type[(fs.st_mode & S_IFMT) >> 13];
    ls->usr_name = my_strtostr(usr->pw_name);
    ls->s2 = my_strlen(ls->usr_name);
    ls->grp_name = my_strtostr(gr->gr_name);
    ls->s3 = my_strlen(ls->grp_name);
    ls_l2(ls, fs, lec);
    (S_ISDIR(fs.st_mode) && param->rec_)?param->file =
    char_realloc(my_realloc(ls->adress, lec->d_name), param->file, param):0;
}

void my_ls(char *file, t_param *param)
{
    struct dirent *lec;
    DIR *rep = opendir(file);
    int i = 0;
    t_ls **all_stat;
    t_ls *ls = malloc(sizeof(t_ls));

    param->blocks = 0;
    (rep == NULL || ls == NULL)?exit(84):0;
    while ((lec = readdir(rep))) {
        (lec == NULL)?exit(84):0;
        i += (lec->d_name[0] != '.')?1:0;
    }
    param->f_size = i;
    all_stat = malloc(sizeof(t_ls *) * (i + 1));
    (all_stat == NULL || closedir(rep) == -1)?exit(84):0;
    fill_stat(file, param, all_stat, ls);
}
