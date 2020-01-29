/*
** EPITECH PROJECT, 2020
** handle_non_builtins.c
** File description:
** mysh (minishell1) : gets the arguments and executes a program if it is found
*/

#include "mysh.h"

int handle_non_builtins(char *input, env_var *env_vars)
{
    char **args = NULL;
    char **env_array = NULL;

    for (; is_separator(*input); input++);
    if (*input == 0)
        return (0);
    if (get_args(&args, input) == 84)
        return (84);
    if (get_env_array(&env_array, env_vars) == 84) {
        for (int i = 0; args[i] != NULL; i++)  // faire comme free_string_array
            free(args[i]);
        free(args);
        return (84);
    }
    //execute_program(args, env_array);
    for (int i = 0; args[i] != NULL; i++) // faire comme free_string_array
        free(args[i]);
    free(args);
    free_string_array(env_array, -1);
    return (0);
}

int get_env_array(char ***env_array, env_var *env_vars)
{
    int length_array = 0;
    env_var *cp_pointer = env_vars;

    for (; cp_pointer != NULL; length_array++, cp_pointer = cp_pointer->next);
    *env_array = malloc(sizeof(char *) * (length_array + 1));
    if (*env_array == NULL)
        return (84);
    for (int i = 0; i < length_array; i++, env_vars = env_vars->next) {
        if (add_var_to_env_array(env_vars, &((*env_array)[i])) == 84) {
            free_string_array(*env_array, i - 1);
            return (84);
        }
    }
    (*env_array)[length_array] = NULL;
    return (0);
}

int add_var_to_env_array(env_var *env_vars, char **var_str)
{
    int length_name = 0;
    int length_value = 0;

    for (; (env_vars->name)[length_name] != 0; length_name++);
    for (; (env_vars->value)[length_value] != 0; length_value++);
    *var_str = malloc(sizeof(char) * (length_name + length_value + 2));
    if (*var_str == NULL)
        return (84);
    for (int i = 0; (env_vars->name)[i] != 0; i++)
        (*var_str)[i] = (env_vars->name)[i];
    (*var_str)[length_name] = '=';
    for (int i = 0; (env_vars->value)[i] != 0; i++)
        (*var_str)[i + length_name + 1] = (env_vars->value)[i];
    (*var_str)[length_name + length_value + 1] = 0;
    return (0);
}

void free_string_array(char **string_arr, int last_string)
{
    if (last_string == -1) {
        for (int i = 0; string_arr[i] != NULL; i++)
            free(string_arr[i]);
    } else {
        for (int i = 0; i <= last_string; i++)
            free(string_arr[i]);
    }
    free(string_arr);
}