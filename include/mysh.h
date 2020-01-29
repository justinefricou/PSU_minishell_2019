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
#include <signal.h>
#include <sys/wait.h>

typedef struct env_var env_var;
struct env_var {
    char *name;
    char *value;
    env_var *next;
};

typedef struct exit_status {
    int go_on;
    u_int8_t value;
} exit_status;

// env_chained_list.c
int get_env_chained_list(char **env, env_var **env_vars);
int get_var_name_and_value_from_env(char **name, char **value, char *var);
int add_var_to_chained_list(char *name, char *value, env_var **list);
void free_chained_list(env_var *list);

// main_loop.c
int main_loop(env_var **env_vars, exit_status *exit_val);
int get_input(char **input, exit_status *exit_val);
int handle_input(char *input, env_var **vars, char **prev_dir, exit_status *ex);
int is_command(char *command, char *input);
int is_a_command(char *input);

// my_exit.c
int my_exit(exit_status *exit_val, char *input);

// launch_cd.c
int launch_cd(char *input, env_var *env_vars, char **previous_dir);
int launch_cd_without_arg(char *input, env_var *env_vars);
char *get_home_path(env_var *env_vars);
int launch_cd_previous_dir(char *input, char *previous_dir);
void update_working_dir(char *current_dir, char **prev_dir, int return_val);

// launch_cd_with_path.c
int launch_cd_with_path(char *input);
int get_path(char **path, char *input);
void display_error_message_chdir(void);

// handle_env_related_builtins.c
int handle_env_related_builtins(char *input, env_var **env_vars);
void launch_env(env_var *env_vars);

// launch_setenv.c
int launch_setenv(env_var *env_vars, char *input);
int get_var_name_and_value_from_input(char **name, char **value, char *input);
int get_var_value_from_input(char **value, char **input);
int get_var_name_from_input(char **name, char **input);
int replace_if_already_in_env(char *name, char *value, env_var *env_vars);

// launch_unsetenv.c
int launch_unsetenv(env_var **env_vars, char *input);
void remove_variable_from_env(char *name, env_var **env_vars);

// handle_non_builtins.c
int handle_non_builtins(char *input, env_var *env_vars);
int get_env_array(char ***env_array, env_var *env_vars);
int add_var_to_env_array(env_var *env_vars, char **var_str);
void free_string_array(char **string_arr, int last_string);

// get_args_program.c
int get_args(char ***args, char *input);
int get_nbr_of_args(char *input);
int get_next_arg(char **arg, char *input, int *i);
void free_previous_args(char **args, int end);

// execute_program.c
int execute_program(char **args, char **env_array);

// my_tools.c
int my_strcmp(char *s1, char *s2);
void my_put_str(char *str);
int is_separator(char c);
int is_int(char *str);
int my_get_nbr(char *s);

#endif // DEF_MYSH