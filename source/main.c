/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** mysh (minishell1) : main function
*/

#include "mysh.h"

int main(int argc, char **argv, char **env)
{
    char *input = NULL;
    int go_on = 1;

    if (argc != 1)
        return (84);
    signal(SIGINT, SIG_IGN);
    while (go_on) {
        write(1, "$> ", 3);
        if (get_input(&input) == 84)
            return (84);
        if (handle_input(input, env, &go_on) == 84) {
            free(input);
            return (84);
        }
        free(input);
    }
    return (0);
}