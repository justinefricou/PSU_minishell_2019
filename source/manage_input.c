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

int handle_input(char *input, int *go_on)
{
    int index = 0;

    for (; input[index] == ' '; index++);
    if (my_strcmp(&(input[index]), "exit") == 0) {
        *go_on = 0;
    }
    return (0);
}