/*
** EPITECH PROJECT, 2020
** execute_program.c
** File description:
** mysh (minishell1) : forks, executes a program and displays errors if any
*/

#include "mysh.h"

int execute_program(char **args, char **env_array)
{
    int return_fork = 0;

    return_fork = fork();
    if (return_fork == 0)
        execute_in_child(args, env_array);
    else if (return_fork > 0)
        wait_for_child(return_fork, args);
    else {
        print_error_message_errno(args[0]);
        return (84);
    }
    return (1);
}

int execute_in_child(char **args, char **env_array)
{
    pid_t pid = 0;

    if (execve(args[0], args, env_array) == -1) {
        print_error_message_errno(args[0]);
        pid = getpid();
        kill(pid, SIGKILL);
        return (84);
    }
    return (1);
}

int wait_for_child(int child_pid, char **args)
{
    int wstatus = 0;

    if (waitpid(child_pid, &wstatus, WUNTRACED) == -1) {
        print_error_message_errno(args[0]);
        return (84);
    }
    if (!WIFEXITED(wstatus))
        print_error_message_wstatus(wstatus);
    return (1);
}

void print_error_message_wstatus(int wstatus)
{
    if (WCOREDUMP(wstatus))
        write(2, "Segmentation fault (core dumped)\n", 33);
}

void print_error_message_errno(char *program_name)
{
    my_put_str(program_name, 2);
    write(2, ": ", 2);
    my_put_str(strerror(errno), 2);
    write(2, ".\n", 2);
}