/*
** EPITECH PROJECT, 2020
** launch_cd_with_path.c
** File description:
** mysh (minishell1) : executing cd with the path given as input
*/

#include "mysh.h"

int launch_cd_with_path(char *input)
{
    char *path = NULL;
    int return_chdir = 0;

    if (get_path(&path, input) == 84)
        return (84);
    return_chdir = chdir(path);
    free(path);
    if (return_chdir != 0) {
        print_error_message_errno("cd");
        return (0);
    }
    return (1);
}

int get_path(char **path, char *input)
{
    int length = 0;

    for (; !is_separator(input[length]) && input[length] != 0; length++);
    *path = malloc(sizeof(char) * (length + 1));
    if (*path == NULL)
        return (84);
    for (int i = 0; i < length; i++)
        (*path)[i] = input[i];
    (*path)[length] = 0;
    return (0);
}