/*
** EPITECH PROJECT, 2020
** env_related_builtins.c
** File description:
** mysh (minishell1) : launches env, setenv and unsetenv builtins
*/

#include "mysh.h"

int handle_env_related_builtins(char *input, char **env)
{
    if (is_command("env", input))
        launch_env(env);
    /*if (is_command("setenv", input)) {
        if (lauch_setenv() == 84)
            return (84);
    } else if (is_command("unsetenv", input)) {
        if (lauch_unsetenv() == 84)
            return (84);
    }*/
    return (0);
}

void launch_env(char **env)
{
    for (int i = 0; env[i] != 0; i++)
        my_put_str(env[i]);
}