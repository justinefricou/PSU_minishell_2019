/*
** EPITECH PROJECT, 2020
** launch_unsetenv.c
** File description:
** mysh (minishell1) : removes a variable from the environment
*/

#include "mysh.h"

int launch_unsetenv(env_var **env_vars, char *input)
{
    int return_val = 1;

    input += 8;
    for (; is_separator(*input); input++);
    if (*input == 0) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        return (0);
    }
    return_val = my_unsetenv(env_vars, input);
    return (return_val);
}

int my_unsetenv(env_var **env_vars, char *input)
{
    char *name = NULL;
    int length = 0;

    while (*input != 0) {
        length = 0;
        for (; !is_separator(input[length]) && input[length] != 0; length++);
        name = malloc(sizeof(char) * (length + 1));
        if (name == NULL)
            return (84);
        for (int i = 0; i < length; i++, input++)
            name[i] = *input;
        name[length] = 0;
        remove_variable_from_env(name, env_vars);
        free(name);
        input++;
        for (; is_separator(*input); input++);
    }
    return (1);
}

void remove_variable_from_env(char *name, env_var **env_vars)
{
    env_var *cpy_prev = NULL, *cpy_pointer1 = NULL, *cpy_pointer2 = *env_vars;

    while (cpy_pointer2 != NULL) {
        cpy_pointer1 = cpy_pointer2;
        cpy_pointer2 = (cpy_pointer2)->next;
        if (my_strcmp(cpy_pointer1->name, name) == 0 && cpy_prev != NULL) {
            cpy_prev->next = cpy_pointer1->next;
            free(cpy_pointer1->name);
            free(cpy_pointer1->value);
            free(cpy_pointer1);
            break;
        } else if (my_strcmp(cpy_pointer1->name, name) == 0) {
            *env_vars = (*env_vars)->next;
            free(cpy_pointer1->name);
            free(cpy_pointer1->value);
            free(cpy_pointer1);
            break;
        }
        cpy_prev = cpy_pointer1;
    }
}