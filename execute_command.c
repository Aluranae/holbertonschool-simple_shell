#include "main.h"
#include <sys/types.h>  /* pour pid_t */
#include <sys/wait.h>   /* pour wait() */
#include <unistd.h>     /* pour fork(), execve(), access() */
#include <stdlib.h>     /* pour exit() */
#include <stdio.h>      /* pour perror() */
#include <string.h>     /* pour strcmp() */

/**
* execute_command - Entry point to execute a command.
* @args: Tokenized command and arguments.
* @argv: Program name (used for error messages).
* @line_number: Input line number.
* @line: Raw user input (for builtins).
*
* Return: 1 to continue loop, exit status on failure.
*/

int execute_command(char **args, char **argv, int line_number, char *line)
{
	char *path;

	(void)argv;
	if (args[0] == NULL)
		return (1);
	if (handle_builtin(args, line) == 1)
		return (0);

	path = find_command_path(args[0]);
	if (!path)
	{
		fprintf(stderr, "./hsh: %d: %s: not found\n", line_number, args[0]);
		return (127);
	}
	if (access(path, X_OK) != 0)
	{
		fprintf(stderr, "./hsh: %d: %s: Permission denied\n", line_number, args[0]);
		free(path);
		return (126);
	}
	return (launch_process(path, args));
}

/**
* launch_process - Fork and execute the command.
* @path: Full path to the command.
* @args: Tokenized command and arguments.
*
* Return: Exit code after execution.
*/

int launch_process(char *path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		execve(path, args, environ);
		perror("execve");
		free(path);
		exit(1);
	}
	else if (pid > 0)
		wait(&status);
	else
		perror("fork");

	free(path);
	return (1);
}
