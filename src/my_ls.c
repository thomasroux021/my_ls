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
    ls->name = lec->d_name;
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
    ls->s1 = len_nbr((int) ls->nlink);
    ls->size = fs.st_size;
    ls->s4 = len_nbr((int) ls->size);
    ls->date = my_time(ctime(&fs.st_mtim.tv_sec));
}

void ls_l(struct dirent *lec, t_ls *ls, t_param *param, char *file)
{
    struct stat fs;
    struct passwd *usr;
    struct group *gr;
    char *type = "pcdb-ls";

    ls->adress = ((file[my_strlen(file) - 1] != '/'))?my_realloc(file,
                    "/"):file;
    (stat(my_realloc(ls->adress, lec->d_name), &fs) == -1)?exit(84):0;
    usr = getpwuid(fs.st_uid);
    gr = getgrgid(fs.st_gid);
    ls->blocks = fs.st_blocks;
    ls->is_dir = type[(fs.st_mode & S_IFMT) >> 13];
    ls->usr_name = my_strtostr(usr->pw_name);
    ls->s2 = my_strlen(ls->usr_name);
    ls->grp_name = my_strtostr(gr->gr_name);
    ls->s3 = my_strlen(ls->grp_name);
    ls->time = (int) fs.st_mtim.tv_sec;
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
    (all_stat == NULL)?exit(84):0;
    closedir(rep);
    fill_stat(file, param, all_stat, ls);
}
