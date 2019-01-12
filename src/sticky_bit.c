/*
** EPITECH PROJECT, 2019
** sticky_bit.c
** File description:
** manage special case
*/

#include "my.h"

void sticky_2(t_ls *ls, struct stat fs)
{
    if (!(fs.st_mode & S_IXGRP) && !(fs.st_mode & S_ISGID))
        ls->x_oth = '-';
    if ((fs.st_mode & S_IXOTH) && (fs.st_mode & S_ISVTX))
        ls->x_oth = 't';
    if (!(fs.st_mode & S_IXOTH) && (fs.st_mode & S_ISVTX))
        ls->x_oth = 'T';
    if ((fs.st_mode & S_IXOTH) && !(fs.st_mode & S_ISVTX))
        ls->x_oth = 'x';
    if (!(fs.st_mode & S_IXOTH) && !(fs.st_mode & S_ISVTX))
        ls->x_oth = '-';
}

void sticky(t_ls *ls, struct stat fs)
{
    if ((fs.st_mode & S_IXUSR) && (fs.st_mode & S_ISUID))
        ls->x_usr = 's';
    if (!(fs.st_mode & S_IXUSR) && (fs.st_mode & S_ISUID))
        ls->x_usr = 'S';
    if ((fs.st_mode & S_IXUSR) && !(fs.st_mode & S_ISUID))
        ls->x_usr = 'x';
    if (!(fs.st_mode & S_IXUSR) && !(fs.st_mode & S_ISUID))
        ls->x_usr = '-';
    if ((fs.st_mode & S_IXGRP) && (fs.st_mode & S_ISGID))
        ls->x_grp = 's';
    if (!(fs.st_mode & S_IXGRP) && (fs.st_mode & S_ISGID))
        ls->x_grp = 'S';
    if ((fs.st_mode & S_IXGRP) && !(fs.st_mode & S_ISGID))
        ls->x_grp = 'x';
    if (!(fs.st_mode & S_IXGRP) && !(fs.st_mode & S_ISGID))
        ls->x_grp = '-';
    sticky_2(ls, fs);
}
