/*
** EPITECH PROJECT, 2019
** my.h
** File description:
** include
*/

#ifndef MY_H
#define MY_H

#include <time.h>
#include <pwd.h>
#include <dirent.h>
#include <grp.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../src/lib/my/lib.h"

typedef struct liked_list
{
    char *data;
    struct liked_list *next;
} linked_list_t;
typedef struct s_param
{
    int l_;
    int rec_;
    int d_;
    int r_;
    int t_;
    int f_size;
    int blocks;
} t_param;
typedef struct s_ls
{
    char *adress;
    char *name;
    blkcnt_t blocks;
    char is_dir;
    char r_usr;
    char w_usr;
    char x_usr;
    char r_grp;
    char w_grp;
    char x_grp;
    char r_oth;
    char w_oth;
    char x_oth;
    nlink_t nlink;
    char *usr_name;
    char *grp_name;
    off_t size;
    int time;
    char *date;
} t_ls;

#endif
