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
    int return_val = 0;
    exit_status exit_val = {1, 0};

    if (argc != 1)
        return (84);
    if (get_env_chained_list(env, &env_vars_list) == 84)
        return (84);
    return_val = main_loop(&env_vars_list, &exit_val);
    if (return_val == -1) {
        write(1, "exit\n", 5);
        return_val = exit_val.value;
    }
    free_chained_list(env_vars_list);
    return (return_val);
}