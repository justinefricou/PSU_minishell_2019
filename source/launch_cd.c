/*
** EPITECH PROJECT, 2020
** launch_cd.c
** File description:
** mysh (minishell1) : executing cd with the options given
*/

#include "mysh.h"

int launch_cd(char *input, env_var *env_vars, char **previous_dir)
{
    char *current_dir = NULL;
    char *buf = NULL;
    size_t size = 0;
    int return_val = 0;

    input += 2;
    for (; is_separator(*input); input++);
    current_dir = getcwd(buf, size);
    return_val = launch_cd_without_arg(input, env_vars);
    if (!return_val)
        return_val = launch_cd_previous_dir(input, *previous_dir);
    if (!return_val)
        return_val = launch_cd_with_path(input);
    update_working_dir(current_dir, previous_dir, return_val);
    if (buf != NULL)
        free(buf);
    return (return_val);
}

int launch_cd_without_arg(char *input, env_var *env_vars)
{
    char *path = NULL;

    if (*input == 0) {
        path = "/home";
        //path = get_home_path(env_vars);
        if (path != NULL) {
            chdir(path);
            return (1);
        }
    }
    return (0);
}

/*char *get_home_path(env_var *env_vars)
{
    while (env_vars != NULL) {
        if (my_strcmp(env_vars->name, "HOME") == 0)
            return (env_vars->value);
        env_vars = env_vars->next;
    }
    return (NULL);
}*/

int launch_cd_previous_dir(char *input, char *previous_dir)
{
    if (*input == '-') {
        if (previous_dir != NULL) {
            chdir(previous_dir);
            return (1);
        } else
            write(2, ": No such file or directory.\n", 29);
    }
    return (0);
}

void update_working_dir(char *current_dir, char **prev_dir, int return_val)
{
    if (return_val == 1 && current_dir != NULL) {
        if (*prev_dir != NULL)
            free(*prev_dir);
        *prev_dir = current_dir;
    }
}