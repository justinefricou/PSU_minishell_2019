/*
** EPITECH PROJECT, 2020
** main_loop.c
** File description:
** mysh (minishell1) : gets the inputs and calls the right functions
*/

#include "mysh.h"

int main_loop(env_var *env_vars)
{
    char *input = NULL;
    int go_on = 1;

    signal(SIGINT, SIG_IGN);
    while (go_on) {
        write(1, "$> ", 3);
        if (get_input(&input) == 84)
            return (84);
        if (handle_input(input, env_vars, &go_on) == 84) {
            free(input);
            return (84);
        }
        free(input);
    }
    return (0);
}

int get_input(char **input)
{
    ssize_t getline_size = 0;
    size_t n = 0;
    int length = 0;

    getline_size = getline(input, &n, stdin);
    if (getline_size < 0)
        return (84);
    for (; (*input)[length] != '\n' && (*input)[length] != 0; length++);
    (*input)[length] = 0;
    return (0);
}

int handle_input(char *input, env_var *env_vars, int *go_on)
{
    for (; *input == ' '; input++);
    if (is_command("exit", input))
        *go_on = 0;
    if (is_command("cd", input))
        launch_cd(input);
    else if (handle_env_related_builtins(input, env_vars) == 84)
        return (84);
    return (0);
}

int is_command(char *command, char *input)
{
    int length_command = 0;

    for (; command[length_command] != 0; length_command++);
    if (my_strcmp(command, input) == 0) {
        input += length_command;
        if (*input == 0 || *input == ' ')
            return (1);
    }
    return (0);
}