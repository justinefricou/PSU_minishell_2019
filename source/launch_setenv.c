/*
** EPITECH PROJECT, 2020
** launch_setenv.c
** File description:
** mysh (minishell1) : adds (or replaces) a variable to the environment
*/

#include "mysh.h"

int launch_setenv(env_var *env_vars, char *input)
{
    char *name = NULL;
    char *value = NULL;
    int return_val = 0;

    input += 6;
    for (; is_separator(*input); input++);
    return_val = get_var_name_and_value_from_input(&name, &value, input);
    if (return_val != 0)
        return (0);
    if (replace_if_already_in_env(name, value, env_vars))
        return (0);
    if (add_var_to_chained_list(name, value, &env_vars) == 84)
        return (84);
    return (0);
}

int get_var_name_and_value_from_input(char **name, char **value, char *input)
{
    int return_val = 0;

    if (get_var_name_from_input(name, &input) == 84)
        return (84);
    for (; is_separator(*input); input++);
    return_val = get_var_value_from_input(value, &input);
    if (return_val != 0)
        free(*name);
    return (return_val);
}

int get_var_name_from_input(char **name, char **input)
{
    int length = 0;

    for (; !is_separator((*input)[length]) && (*input)[length] != 0; length++);
    *name = malloc(sizeof(char) * (length + 1));
    if (*name == NULL)
        return (84);
    for (int i = 0; i < length; i++, (*input)++)
        (*name)[i] = **input;
    (*name)[length] = 0;
    return (0);
}

int get_var_value_from_input(char **value, char **input)
{
    int len = 0;

    if (**input == '"' || **input == '\'') {
        for (; (*input)[len + 1] != **input && (*input)[len + 1] != 0; len++);
        (*input)++;
        if ((*input)[len] == 0) {
            write(2, "Unmatched '\"'\n", 14);
            return (1);
        }
    } else
        for (; !is_separator((*input)[len]) && (*input)[len] != 0; len++);
    *value = malloc(sizeof(char) * (len + 1));
    if (*value == NULL)
        return (84);
    for (int i = 0; i < len; i++, (*input)++)
        (*value)[i] = **input;
    (*value)[len] = 0;
    return (0);
}

int replace_if_already_in_env(char *name, char *value, env_var *env_vars)
{
    while (env_vars != NULL) {
        if (my_strcmp(env_vars->name, name) == 0) {
            free(env_vars->name);
            env_vars->name = name;
            free(env_vars->value);
            env_vars->value = value;
            return (1);
        }
        env_vars = env_vars->next;
    }
    return (0);
}