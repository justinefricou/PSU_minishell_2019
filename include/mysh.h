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
    char *name;
    char *value;
    env_var *next;
};

// env_chained_list.c
int get_env_chained_list(char **env, env_var **env_vars);
int get_var_name_and_value_from_env(char **name, char **value, char *var);
int add_var_to_chained_list(char *name, char *value, env_var **list);
void free_chained_list(env_var *list);

// main_loop.c
int main_loop(env_var **env_vars);
int get_input(char **input);
int handle_input(char *input, env_var **env_vars, char **prev_dir, int *go_on);
int is_command(char *command, char *input);

// handle_env_related_builtins.c
int handle_env_related_builtins(char *input, env_var **env_vars);
void launch_env(env_var *env_vars);

// launch_setenv.c
int launch_setenv(env_var *env_vars, char *input);
int get_var_name_and_value_from_input(char **name, char **value, char *input);
int get_var_value_from_input(char **value, char **input);
int get_var_name_from_input(char **name, char **input);
int replace_if_already_in_env(char *name, char *value, env_var *env_vars);

// launch_unsetenv.c
int launch_unsetenv(env_var **env_vars, char *input);
void remove_variable_from_env(char *name, env_var **env_vars);

// launch_cd.c
int launch_cd(char *input, env_var *env_vars, char **previous_dir);
int launch_cd_without_arg(char *input, env_var *env_vars);
int launch_cd_previous_dir(char *input, char *previous_dir);
char *get_home_path(env_var *env_vars);

// my_tools.c
int my_strcmp(char *s1, char *s2);
void my_put_str(char *str);
int is_separator(char c);

#endif // DEF_MYSH