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
    int n_arg;
    int i;
    char **file;
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
    int *s1;
    int *s2;
    int *s3;
    int *s4;
} t_ls;
t_ls **sort_int(t_param *param, t_ls **all_stat);
t_param *my_param(int ac, char **av);
char **pars_file(int ac, char **av, t_param *param);
char *my_time(char *time);
void ls_l(struct dirent *lec, t_ls *ls, t_param *param);
void print_ls(t_param *param, t_ls **all_stat);
void my_ls(char *file, t_param *param);

int my_printf(char *str, ...);
void flag3(char *str, int i, va_list list);
void signe(int i);
void unsign(unsigned int i, int base, int maj);
void pointer(long x);
int charisflag(char c);
char *parser(char *str);
char *fill(char *result, int len);
char *clean_zero(char *result);
char *chartostr(char c);
char *octal(char c);
void decitobase(long i, int base, int maj);
void flag1(char *str, int i, va_list list);
void flag2(char *str, int i, va_list list);
int sum_stdarg(int i, int nb, ...);
void my_concat_list(linked_list_t **begin, linked_list_t *begin2);
void destroye_linked_list_t(linked_list_t *element);
void delete_link(linked_list_t **begin, linked_list_t *element);
int my_delete_nodes(linked_list_t **begin, void const *data_ref, int (*cmp)());
int my_list_size(linked_list_t const *begin);
int my_charlist_size(linked_list_t *list);
char *my_linkedtostr(linked_list_t *list);
linked_list_t *add_element_at_begin(linked_list_t **list, char *data);
linked_list_t *my_params_to_list(int ac, char * const *av);
void print_list(linked_list_t *s);
void my_rev_list(linked_list_t **begin);
int disp_stdarg(char *s, ...);
#endif
