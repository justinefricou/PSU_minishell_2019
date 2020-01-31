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

    nbr_of_args = get_nbr_of_args(input);
    if (nbr_of_args < 0)
        return (0);
    *args = malloc(sizeof(char *) * (nbr_of_args + 1));
    if (*args == NULL)
        return (84);
    for (int j = 0; j < nbr_of_args; j++) {
        if (get_next_arg(&((*args)[j]), &input) == 84) {
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
    int len = 0;

    for (; *input != 0; nbr_of_args++) {
        for (; is_separator(*input); input++);
        if (handle_quotes(&input, &len) == -1)
            return (-1);
        for (; !is_separator(*input) && *input != 0; input++);
        for (; is_separator(*input); input++);
    }
    return (nbr_of_args);
}

int handle_quotes(char **input, int *len)
{
    if (**input == '"' || **input == '\'') {
        while ((*input)[*len + 1] != **input && (*input)[*len + 1] != 0)
            (*len)++;
        (*input)++;
        if ((*input)[*len] == 0) {
            write(2, "Unmatched '", 11);
            write(2, (*input) - 1, 1);
            write(2, "'.\n", 3);
            return (-1);
        }
        (*input) += *len;
        return (1);
    }
    return (0);
}

int get_next_arg(char **arg, char **input)
{
    int len = 0;
    int quotes = 0;

    for (; is_separator(**input); (*input)++);
    if (**input == '"' || **input == '\'') {
        for (; (*input)[len + 1] != **input && (*input)[len + 1] != 0; len++);
        (*input)++;
        quotes = 1;
    } else
        for (; !is_separator((*input)[len]) && (*input)[len] != 0; len++);
    *arg = malloc(sizeof(char) * (len + 1));
    if (*arg == NULL)
        return (84);
    for (int i = 0; i < len; i++, (*input)++)
        (*arg)[i] = **input;
    (*arg)[len] = 0;
    if (quotes)
        (*input) += 2;
    return (1);
}