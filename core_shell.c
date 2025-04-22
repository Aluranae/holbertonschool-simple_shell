#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pour isatty */
#include <string.h>

/**
 * core_shell - Entry point of the shell.
 * Handles the main loop: prompt display, input reading,
 * parsing, command execution, and memory cleanup.
 * @argv: Array of arguments (used for error messages like argv[0]).
 * Return: Always 0.
 */

int core_shell(char **argv)
{
	char *line = NULL, **args;
	int line_number = 1, result, last_status = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_input();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}

		if (is_line_empty(line))
		{
			free(line);
			continue;
		}

		args = split_line(line);
		if (args == NULL)
		{
			free(line);
			continue;
		}

		/* Gestion de la commande "exit" */
		if (handle_exit(args, line))
		{
			free(args);
			free(line);
			break;
		}

		result = execute_command(args, argv, line_number, line);
		free(args);
		free(line);
		line_number++;

		last_status = result;

		if (result == -1)
			break;
	}
	return (last_status);
}
