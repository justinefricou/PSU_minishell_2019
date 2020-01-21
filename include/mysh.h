/*
** EPITECH PROJECT, 2020
** mysh.h
** File description:
** mysh (minishell1) : header
*/

#ifndef DEF_MYSH
#define DEF_MYSH

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// manage_input.c
int get_input(char **buffer);
int handle_input(char *input, int *go_on);

// my_tools.c
int my_strcmp(char *s1, char *s2);

#endif // DEF_MYSH