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
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

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
int my_unsetenv(env_var **env_vars, char *input);
void remove_variable_from_env(char *name, env_var **env_vars);

// handle_non_builtins.c
int handle_non_builtins(char *input, env_var *env_vars);
int get_env_array(char ***env_array, env_var *env_vars);
int add_var_to_env_array(env_var *env_vars, char **var_str);
void free_string_array(char **string_arr, int last_string);

// get_args_program.c
int get_args(char ***args, char *input, env_var *env_vars);
int get_nbr_of_args(char *input);
int handle_quotes(char **input, int *len);
int get_next_arg(char **arg, char **input);

// get_argv0.c
int get_path_program(char **args, env_var *env_vars);
int check_existence(char **args, char **path_program, env_var *env_vars);
int check_access(char *path_program, char *program_name);

// go_through_path.c
int find_program_in_path(char *argv0, char **path_program, env_var *env_vars);
int get_path_from_env(char **path, env_var *env_vars);
int get_next_path(char **next_path, char *argv0, char **path);
int my_strcat(char *str1, char *str2, char **final_str);

// execute_program.c
int execute_program(char **args, char **env_array);
int execute_in_child(char **args, char **env_array);
int wait_for_child(int child_pid, char **args);
void print_error_message_wstatus(int wstatus);
void print_error_message_errno(char *program_name);

// my_tools.c
int my_strcmp(char *s1, char *s2);
void my_put_str(char *str, int fd);
int is_separator(char c);
int is_int(char *str);
int my_get_nbr(char *s);

#endif // DEF_MYSH