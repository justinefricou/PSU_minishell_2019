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

// manage_input.c
int get_input(char **buffer);
int handle_input(char *input, char **env, int *go_on);
int is_command(char *command, char *input);

// launch_cd.c
void launch_cd(char *option);

// env_related_builtins.c
int handle_env_related_builtins(char *input, char **env);
void launch_env(char **env);

// my_tools.c
int my_strcmp(char *s1, char *s2);
void my_put_str(char *str);

#endif // DEF_MYSH