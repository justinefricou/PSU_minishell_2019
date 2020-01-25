/*
** EPITECH PROJECT, 2020
** my_tools.c
** File description:
** mysh (minishell1) : several tools
*/

#include "mysh.h"

void my_put_str(char *str)
{
    int length = 0;

    for (; str[length] != 0; length++);
    write(1, str, length);
}