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

    input += 6;
    for (; *input == ' '; input++);
    if (get_var_name_and_value_from_input(&name, &value, input) == 84)
        return (84);
    if (replace_if_already_in_env(name, value, env_vars))
        return (0);
    if (add_var_to_chained_list(name, value, &env_vars) == 84)
        return (84);
    return (0);
}

int get_var_name_and_value_from_input(char **name, char **value, char *input)
{
    int name_len = 0, value_len = 0;

    for (; input[name_len] != ' ' && input[name_len] != 0; name_len++);
    *name = malloc(sizeof(char) * (name_len + 1));
    if (*name == NULL)
        return (84);
    for (int i = 0; i < name_len; i++, input++)
        (*name)[i] = *input;
    (*name)[name_len] = 0;
    for (; *input == ' '; input++);
    for (; input[value_len] != ' ' && input[value_len] != 0; value_len++);
    *value = malloc(sizeof(char) * (value_len + 1));
    if (*value == NULL) {
        free(*name);
        return (84);
    }
    for (int i = 0; i < value_len; i++, input++)
        (*value)[i] = *input;
    (*value)[value_len] = 0;
    return (0);
}

int replace_if_already_in_env(char *name, char *value, env_var *env_vars)
{
    while (env_vars != NULL) {
        if (my_strcmp(env_vars->name, name) == 0) {
            env_vars->value = value;
            return (1);
        }
        env_vars = env_vars->next;
    }
    return (0);
}