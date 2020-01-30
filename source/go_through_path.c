/*
** EPITECH PROJECT, 2020
** go_through_path.c
** File description:
** mysh (minishell1) : tries to find the program called in the path
*/

#include "mysh.h"

int find_program_in_path(char *argv0, char **path_program, env_var *env_vars) //
{
    char *path = NULL;
    char *next_path = NULL;

    if (!get_path_from_env(&path, env_vars))
        return (0);
    while (*path != 0) {
        if (get_next_path(&next_path, argv0, &path) == 84)
            return (0);
        if (access(next_path, F_OK) == 0) {
            *path_program = next_path;
            return (1);
        }
        free(next_path);
    }
    return (0);
}

int get_path_from_env(char **path, env_var *env_vars)
{
    while (env_vars != NULL) {
        if (my_strcmp(env_vars->name, "PATH") == 0) {
            *path = env_vars->value;
            return (1);
        }
        env_vars = env_vars->next;
    }
    return (0);
}

int get_next_path(char **next_path, char *argv0, char **path)
{
    int length = 0;
    char *first_half = NULL;

    for (; (*path)[length] != ':' && (*path)[length] != 0; length++);
    first_half = malloc(sizeof(char) * (length + 1));
    if (first_half == NULL)
        return (84);
    for (int i = 0; i < length; i++, (*path)++)
        (first_half)[i] = **path;
    (first_half)[length] = 0;
    if (my_strcat(first_half, argv0, next_path) == 84) {
        free(first_half);
        return (84);
    }
    if (**path == ':')
        (*path)++;
    return (0);
}

int my_strcat(char *str1, char *str2, char **final_str)
{
    int len_1 = 0;
    int len_2 = 0;

    for (; str1[len_1] != 0; len_1++);
    for (; str2[len_2] != 0; len_2++);
    *final_str = malloc(sizeof(char) * (len_1 + len_2 + 2));
    if (*final_str == NULL)
        return (84);
    for (int i = 0; i < len_1; i++)
        (*final_str)[i] = str1[i];
    (*final_str)[len_1] = '/';
    for (int i = 0; i < len_2; i++)
        (*final_str)[len_1 + i + 1] = str2[i];
    (*final_str)[len_1 + len_2 + 1] = 0;
    return (0);
}