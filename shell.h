#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

pid_t get_pid(void);
void exit_shell(char *command);
int print_env(char **env);
int handle_builtin(char **args, char **env);

#endif
