/*
** EPITECH PROJECT, 2020
** get_argv0.c
** File description:
** mysh (minishell1) : gets the path of the program to execute
*/

#include "mysh.h"

int get_path_program(char **args, env_var *env_vars)
{
    char *path_program = NULL;

    if (!check_existence(args, &path_program, env_vars))
        return (0);
    if (!check_access(path_program, args[0])) {
        if (path_program != args[0] && path_program != NULL)
            free(path_program);
        return (0);
    }
    if (path_program != args[0])
        free(args[0]);
    args[0] = path_program;
    return (1);
}

int check_existence(char **args, char **path_program, env_var *env_vars)
{
    if (args[0][0] == '.') {
        if (access(args[0], F_OK) != 0) {
            my_put_str(args[0], 2);
            write(2, ": Command not found.\n", 21);
            return (0);
        }
        *path_program = args[0];
    } else if (!find_program_in_path(args[0], path_program, env_vars)) {
        my_put_str(args[0], 2);
        write(2, ": Command not found.\n", 21);
        free(*path_program);
        return (0);
    }
    return (1);
}

int check_access(char *path_program, char *program_name)
{
    if (access(path_program, X_OK) != 0) {
        my_put_str(program_name, 2);
        write(2, ": Permission denied.\n", 21);
        return (0);
    }
    return (1);
}