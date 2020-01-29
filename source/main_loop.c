/*
** EPITECH PROJECT, 2020
** main_loop.c
** File description:
** mysh (minishell1) : gets the inputs and calls the right functions
*/

#include "mysh.h"

int main_loop(env_var **env_vars, exit_status *exit_val)
{
    char *input = NULL;
    char *previous_dir = NULL;
    int val_return = 0;

    signal(SIGINT, SIG_IGN);
    while (exit_val->go_on) {
        write(1, "$> ", 3);
        if (get_input(&input, exit_val) == -1)
            return (-1);
        val_return = handle_input(input, env_vars, &previous_dir, exit_val);
        if (val_return != 0)
            exit_val->go_on = 0;
        free(input);
    }
    if (previous_dir != NULL)
        free(previous_dir);
    return (val_return);
}

int get_input(char **input, exit_status *exit_val)
{
    ssize_t getline_size = 0;
    size_t n = 0;
    int length = 0;

    getline_size = getline(input, &n, stdin);
    if (getline_size < 0) {
        exit_val->go_on = 0;
        return (-1);
    }
    for (; (*input)[length] != '\n' && (*input)[length] != 0; length++);
    (*input)[length] = 0;
    return (0);
}

int handle_input(char *input, env_var **vars, char **prev_dir, exit_status *ex)
{
    int return_val = 0;

    for (; is_separator(*input); input++);
    if (handle_env_related_builtins(input, vars) == 84)
        return (84);
    if (is_command("exit", input)) {
        if (my_exit(ex, input) == 0)
            return (-1);
    } else if (is_command("cd", input)) {
        if (launch_cd(input, *vars, prev_dir) == 84)
            return (84);
    }
    if (!is_a_command(input))
        execute_program(input, env_vars); // bootstrap
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

int is_a_command(char *input)
{
    char *commands[] = {"exit", "cd", "env", "setenv", "unsetenv"};

    for (int i = 0; i < 5; i++) {
        if (is_command(commands[i], input))
            return (1);
    }
    return (0);
}