/*
** EPITECH PROJECT, 2020
** env_chained_list.c
** File description:
** mysh (minishell1) : tools for environment variables chained list
*/

#include "mysh.h"

int get_env_chained_list(char **env, env_var **env_vars)
{
    for (; *env != NULL; env++) {
        if (add_var_to_chained_list(*env, env_vars) == 84) {
            free_chained_list(*env_vars);
            return (84);
        }
    }
    return (0);
}

int add_var_to_chained_list(char *var, env_var **list)
{
    env_var *new_env_var = NULL;
    env_var *pointer = NULL;

    new_env_var = malloc(sizeof(env_var));
    if (new_env_var == NULL)
        return (84);
    new_env_var->str = var;
    new_env_var->next = NULL;
    if (*list == NULL)
        *list = new_env_var;
    else {
        pointer = *list;
        for (; pointer->next != NULL; pointer = pointer->next);
        pointer->next = new_env_var;
    }
    return (0);
}

void free_chained_list(env_var *list)
{
    env_var *copy_pointer = NULL;

    while (list != NULL) {
        copy_pointer = list;
        list = list->next;
        free(copy_pointer);
    }
}