/*
** EPITECH PROJECT, 2019
** main.c
** File description:
** main
*/

#include "my.h"

int parser(int ac, char **av)
{
    return (0);
}

void ls_l(int ac, char **av, struct dirent *lec)
{
    struct stat fs;
    struct passwd *inf;
    stat(lec->d_name, &fs);
    inf = getpwuid(fs.st_uid);
    if (ac > 1 && !my_strcmp(av[1], "-l")) {
        my_putstr(inf->pw_name);
        my_putchar(' ');
    }
}

int main(int ac, char **av)
{
    struct dirent *lec;
    DIR *rep = opendir(".");

    my_put_nbr(ac);
    if (ac > 1)
        parser(ac, av);
    while ((lec = readdir(rep))) {
        if (lec->d_name[0] != '.') {
            ls_l(ac, av, lec);
            my_putstr(lec->d_name);
            my_putchar('\n');
        }
    }
    closedir(rep);
}
