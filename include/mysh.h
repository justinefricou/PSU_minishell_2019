/*
** EPITECH PROJECT, 2020
** mysh.h
** File description:
** mysh (minishell1) : header
*/

#ifndef DEF_MYSH
#define DEF_MYSH

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

typedef struct env_var env_var;
struct env_var {
    char *str;
    env_var *next;
};

// env_chained_list.c
int get_env_chained_list(char **env, env_var **env_vars);
int add_var_to_chained_list(char *var, env_var **list);
void free_chained_list(env_var *list);

// main_loop.c
int main_loop(env_var *env_vars);
int get_input(char **input);
int handle_input(char *input, env_var *env_vars, int *go_on);
int is_command(char *command, char *input);

// launch_cd.c
void launch_cd(char *option);

// env_related_builtins.c
int handle_env_related_builtins(char *input, env_var *env_vars);
void launch_env(env_var *env_vars);

// my_tools.c
int my_strcmp(char *s1, char *s2);
void my_put_str(char *str);

#endif // DEF_MYSH