/*
** EPITECH PROJECT, 2020
** env_related_builtins.c
** File description:
** mysh (minishell1) : launches env, setenv and unsetenv builtins
*/

#include "mysh.h"

int handle_env_related_builtins(char *input, env_var *env_vars)
{
    if (is_command("env", input))
        launch_env(env_vars);
    /*if (is_command("setenv", input)) {
        if (lauch_setenv() == 84)
            return (84);
    } else if (is_command("unsetenv", input)) {
        if (lauch_unsetenv() == 84)
            return (84);
    }*/
    return (0);
}

void launch_env(env_var *env_vars)
{
    while (env_vars != NULL) {
        my_put_str(env_vars->str);
        write(1, "\n", 1);
        env_vars = env_vars->next;
    }
}