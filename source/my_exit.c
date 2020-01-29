/*
** EPITECH PROJECT, 2020
** my_exit.c
** File description:
**  mysh (minishell1) : sets the exit value and tells the program to stop
*/

#include "mysh.h"

int my_exit(exit_status *exit_val, char *input)
{
    input += 4;
    for (; is_separator(*input); input++);
    if (*input == 0) {
        exit_val->go_on = 0;
        exit_val->value = 0;
        return (0);
    }
    if (!('0' <= *input && *input <= '9') && *input != '-' && *input != '+') {
        write(2, "exit: Expression Syntax.\n", 25);
        return (-1);
    } else if (!is_int(input)) {
        write(2, "exit: Badly formed number.\n", 27);
        return (-1);
    }
    exit_val->go_on = 0;
    exit_val->value = my_get_nbr(input);
    return (0);
}