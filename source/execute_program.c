/*
** EPITECH PROJECT, 2020
** execute_program.c
** File description:
** mysh (minishell1) : forks, executes a program and displays errors if any
*/

#include "mysh.h"

int execute_program(char **args, char **env_array)
{
    int wstatus = 0;
    int return_fork = 0;

    return_fork = fork();
    if (return_fork == 0) {
        if (execve(args[0], args, env_array) == -1) // afficher message si erreur
            return (84);
    } else if (return_fork > 0) {
        if (wait(&wstatus) == -1)
            return (84);
        /*if (WIFEXITED(wstatus))
            write(1, "OK\n", 3);
        if (WTERMSIG(wstatus))
            write(1, "Segmentation fault\n", 19);*/
    } else
        return (84);
    return (0);
}

