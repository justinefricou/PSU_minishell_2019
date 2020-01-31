/*
** EPITECH PROJECT, 2020
** handle_env_related_builtins.c
** File description:
** mysh (minishell1) : launches env, setenv and unsetenv builtins
*/

#include "mysh.h"

int handle_env_related_builtins(char *input, env_var **env_vars)
{
    int return_val = 0;

    if (is_command("env", input))
        launch_env(*env_vars);
    if (is_command("setenv", input)) {
        return_val = launch_setenv(*env_vars, input);
        if (return_val == 2)
            launch_env(*env_vars);
    } else if (is_command("unsetenv", input))
        return_val = launch_unsetenv(env_vars, input);
    return (return_val);
}

void launch_env(env_var *env_vars)
{
    while (env_vars != NULL) {
        my_put_str(env_vars->name, 1);
        write(1, "=", 1);
        my_put_str(env_vars->value, 1);
        write(1, "\n", 1);
        env_vars = env_vars->next;
    }
}