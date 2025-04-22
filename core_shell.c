#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> /* pour isatty */
#include <string.h>

/**
 * main - Entry point of the shell.
 * Handles the main loop: prompt display, input reading,
 * parsing, command execution, and memory cleanup.
 * @argc: Number of arguments passed to the program (unused).
 * @argv: Array of arguments (used for error messages like argv[0]).
 * Return: Always 0.
 */

int main(int argc, char **argv)
{
	char *line = NULL, **args;
	int line_number = 1, result;

	(void)argc; /* inutilisé */

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);

		line = read_input();
		if (line == NULL) /* Ctrl+D */
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

		result = execute_command(args, argv, line_number, line);
		free(args);
		free(line);
		line_number++;

		if (result == -1)
			break;
	}
	return (result);
}
