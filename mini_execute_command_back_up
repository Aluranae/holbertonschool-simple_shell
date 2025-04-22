#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

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
	pid_t pid;
	int status;
	(void)line;

	/* Étape 1 : Vérifier si l'entrée est vide */
	if (args[0] == NULL)
		return (1);

	/* Étape 2 : Vérifier si la commande est exécutable directement */
	if (access(args[0], X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_number, args[0]);
		return (127);
	}

	/* Étape 3 : Créer un processus fils */
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	/* Étape 4 : Dans le fils, exécuter la commande */
	if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		/* Étape 5 : Attendre la fin du processus fils */
		wait(&status);
	}

	/* Étape 6 : Retourner 1 pour continuer */
	return (1);
}
