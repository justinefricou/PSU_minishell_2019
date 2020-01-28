/*
** EPITECH PROJECT, 2020
** main_loop.c
** File description:
** mysh (minishell1) : gets the inputs and calls the right functions
*/

#include "mysh.h"

int main_loop(env_var **env_vars)
{
    char *input = NULL;
    char *previous_dir = NULL;
    int go_on = 1;
    int val_return = 0;

    signal(SIGINT, SIG_IGN);
    while (go_on) {
        write(1, "$> ", 3);
        if (get_input(&input) == -1)
            return (-1);
        val_return = handle_input(input, env_vars, &previous_dir, &go_on);
        if (val_return != 0)
            go_on = 0;
        free(input);
    }
    if (previous_dir != NULL)
        free(previous_dir);
    return (val_return);
}

int get_input(char **input)
{
    ssize_t getline_size = 0;
    size_t n = 0;
    int length = 0;

    getline_size = getline(input, &n, stdin);
    if (getline_size < 0)
        return (-1);
    for (; (*input)[length] != '\n' && (*input)[length] != 0; length++);
    (*input)[length] = 0;
    return (0);
}

int handle_input(char *input, env_var **env_vars, char **prev_dir, int *go_on)
{
    for (; is_separator(*input); input++);
    if (is_command("exit", input)) {
        *go_on = 0;
        return (-1);
    }
    if (is_command("cd", input)) {
        if (launch_cd(input, *env_vars, prev_dir) == 84)
            return (84);
    } else if (handle_env_related_builtins(input, env_vars) == 84)
        return (84);
    return (0);
}

int is_command(char *command, char *input)
{
    int length_command = 0;

    for (; command[length_command] != 0; length_command++);
    for (int i = 0; i < length_command; i++) {
        if (command[i] != input[i])
            return (0);
    }
    input += length_command;
    if (*input != 0 && !is_separator(*input))
        return (0);
    return (1);
}