#ifndef SHELL_H
#define SHELL_H

#include <sys/types.h>

int print_env(char **env);
void exit_shell(char *command);
pid_t get_pid(void);

#endif
