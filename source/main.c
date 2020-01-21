/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** mysh (minishell1) : main function
*/

#include "mysh.h"

int main(int argc, char **argv)
{
    char *input = NULL;
    int go_on = 1;

    while (go_on) {
        write(1, "$> ", 3);
        if (get_input(&input) == 84)
            return (84);
        if (handle_input(input, &go_on) == 84) {
            free(input);
            return (84);
        }
        free(input);
    }
    return (0);
}