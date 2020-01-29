/*
** EPITECH PROJECT, 2020
** handle_non_builtins.c
** File description:
** mysh (minishell1) : executes a program if it is found
*/

#include "mysh.h"

int handle_non_builtins(char *input, env_var *env_vars)
{
    char **args = NULL;

    for (; is_separator(*input); input++);
    if (*input == 0)
        return (0);
    if (get_args(&args, input) == 84)
        return (84);
    //execute_program(args, env_vars);
    for (int i = 0; args[i] != NULL; i++)
        free(args[i]);
    free(args);
    return (0);
}

int get_args(char ***args, char *input)
{
    int nbr_of_args = 0;
    int i = 0;

    nbr_of_args = get_nbr_of_args(input);
    *args = malloc(sizeof(char *) * (nbr_of_args + 1));
    if (*args == NULL)
        return (84);
    for (int j = 0; j < nbr_of_args; j++) {
        if (get_next_arg(&((*args)[j]), input, &i) == 84) {
            free_previous_args(*args, j);
            free(*args);
            return (84);
        }
    }
    (*args)[nbr_of_args] = NULL;
    return (0);
}

int get_nbr_of_args(char *input)
{
    int nbr_of_args = 0;

    for (int i = 0; input[i] != 0; nbr_of_args++) {
        for (; is_separator(input[i]); i++);
        for (; !is_separator(input[i]) && input[i] != 0; i++);
        for (; is_separator(input[i]); i++);
    }
    return (nbr_of_args);
}

int get_next_arg(char **arg, char *input, int *i)
{
    int len = 0;
    int i_s = *i;

    for (; is_separator(input[i_s]); i_s++, (*i)++);
    for (; !is_separator(input[i_s + len]) && input[i_s + len] != 0; (*i)++)
        len++;
    *arg = malloc(sizeof(char) * (len + 1));
    if (arg == NULL)
        return (84);
    for (int j = 0; j < len; j++)
        (*arg)[j] = input[i_s + j];
    (*arg)[len] = 0;
    return (0);
}

void free_previous_args(char **args, int end)
{
    for (int i = 0; i < end; i++)
        free(args[i]);
}