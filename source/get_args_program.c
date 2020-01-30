/*
** EPITECH PROJECT, 2020
** get_args_program.c
** File description:
** mysh (minishell1) : gets the arguments of the program from the input
*/

#include "mysh.h"

int get_args(char ***args, char *input, env_var *env_vars)
{
    int nbr_of_args = 0;
    int i = 0;

    nbr_of_args = get_nbr_of_args(input);
    *args = malloc(sizeof(char *) * (nbr_of_args + 1));
    if (*args == NULL)
        return (84);
    for (int j = 0; j < nbr_of_args; j++) {
        if (get_next_arg(&((*args)[j]), input, &i) == 84) {
            free_string_array(*args, j - 1);
            return (84);
        }
    }
    (*args)[nbr_of_args] = NULL;
    if (!get_path_program(*args, env_vars)) {
        free_string_array(*args, -1);
        return (0);
    }
    return (1);
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

int get_path_program(char **args, env_var *env_vars)
{
    char *path_program = NULL;

    if (access(args[0], F_OK) == 0)
        path_program = args[0];
    else if (!find_program_in_path(args[0], &path_program, env_vars)) {
        my_put_str(args[0]);
        write(2, ": Command not found.\n", 21);
        return (0);
    }
    if (access(path_program, X_OK) != 0) {
        my_put_str(args[0]);
        write(2, ": Permission denied.\n", 21);
        return (0);
    }
    if (args[0] != path_program) {
        free(args[0]);
        args[0] = path_program;
    }
    return (1);
}