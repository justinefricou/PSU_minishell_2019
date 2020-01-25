/*
** EPITECH PROJECT, 2020
** my_tools.c
** File description:
** mysh (minishell1) : several tools
*/

#include "mysh.h"

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    for (; s1[i] != 0 && s2[i] != 0 && s1[i] != ' ' && s2[i] != ' '; i++) {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return (0);
}

void my_put_str(char *str)
{
    int length = 0;

    for (; str[length] != 0; length++);
    write(1, str, length);
}