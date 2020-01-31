/*
** EPITECH PROJECT, 2020
** my_tools.c
** File description:
** mysh (minishell1) : several tools
*/

#include "mysh.h"

void my_put_str(char *str, int fd)
{
    int length = 0;

    for (; str[length] != 0; length++);
    write(fd, str, length);
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    for (; s1[i] != 0 && s2[i] != 0; i++) {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
    }
    return (s1[i] - s2[i]);
}

int is_separator(char c)
{
    if (c == ' ' || c == '\t')
        return (1);
    return (0);
}

int is_int(char *str)
{
    int i = 0;

    if (str[i] == '-' || str[i] == '+')
        i++;
    for ( ; str[i] != 0; i++) {
        if (str[i] < '0' || '9' < str[i])
            return (0);
    }
    return (1);
}

int my_get_nbr(char *s)
{
    int nbr = 0;
    int i = 0;

    for (; s[i] == '-' || s[i] == '+' || s[i] == '0'; i++);
    for (; s[i] != 0 && !is_separator(s[i]); i++)
        nbr = nbr * 10 + (s[i] - 48);
    if (s[0] == '-')
        nbr = nbr * (-1);
    return (nbr);
}