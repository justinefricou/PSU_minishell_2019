/*
** EPITECH PROJECT, 2020
** env_chained_list.c
** File description:
** mysh (minishell1) : tools for environment variables chained list
*/

#include "mysh.h"

int get_env_chained_list(char **env, env_var **env_vars)
{
    char *name = NULL;
    char *value = NULL;

    for (; *env != NULL; env++) {
        if (get_var_name_and_value_from_env(&name, &value, *env) == 84) {
            free_chained_list(*env_vars);
            return (84);
        }
        if (add_var_to_chained_list(name, value, env_vars) == 84) {
            free_chained_list(*env_vars);
            return (84);
        }
    }
    return (0);
}

int get_var_name_and_value_from_env(char **name, char **value, char *var)
{
    int name_len = 0;
    int value_len = 0;

    for (; var[name_len] != '='; name_len++);
    for (; var[value_len + name_len + 1] != 0; value_len++);
    *name = malloc(sizeof(char) * (name_len + 1));
    if (*name == NULL)
        return (84);
    *value = malloc(sizeof(char) * (value_len + 1));
    if (*value == NULL) {
        free(*name);
        return (84);
    }
    for (int i = 0; i < name_len; i++)
        (*name)[i] = var[i];
    (*name)[name_len] = 0;
    for (int i = 0; i < value_len; i++)
        (*value)[i] = var[i + name_len + 1];
    (*value)[value_len] = 0;
    return (0);
}

int add_var_to_chained_list(char *name, char *value, env_var **list)
{
    env_var *new_env_var = NULL;
    env_var *pointer = NULL;

    new_env_var = malloc(sizeof(env_var));
    if (new_env_var == NULL)
        return (84);
    new_env_var->name = name;
    new_env_var->value = value;
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
        free(copy_pointer->name);
        free(copy_pointer->value);
        free(copy_pointer);
    }
}