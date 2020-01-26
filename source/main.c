/*
** EPITECH PROJECT, 2020
** main.c
** File description:
** mysh (minishell1) : main function
*/

#include "mysh.h"

int main(int argc, char **argv, char **env)
{
    env_var *env_vars_list = NULL;

    if (argc != 1)
        return (84);
    if (get_env_chained_list(env, &env_vars_list) == 84)
        return (84);
    if (main_loop(env_vars_list) == 84) {
        free_chained_list(env_vars_list);
        return (84);
    }
    free_chained_list(env_vars_list);
    return (0);
}