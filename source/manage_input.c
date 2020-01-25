/*
** EPITECH PROJECT, 2020
** manage_input.c
** File description:
** mysh (minishell1) : gets the input and calls the right function
*/

#include "mysh.h"

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

int handle_input(char *input, char **env, int *go_on)
{
    for (; *input == ' '; input++);
    if (is_command("exit", input))
        *go_on = 0;
    if (is_command("cd", input))
        launch_cd(input);
    else if (handle_env_related_builtins(input, env) == 84)
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