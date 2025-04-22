#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * execute_command - Exécute une commande avec ou sans PATH.
 * @args: Commande tokenisée (ex: {"ls", NULL}).
 * @argv: Nom du programme (argv[0]) pour les messages d'erreur.
 * @line_number: Numéro de ligne pour affichage en cas d'erreur.
 * @line: Ligne brute de l'utilisateur (non utilisée ici).
 *
 * Return: Code de sortie de la commande ou code d’erreur (127, 126).
 */
int execute_command(char **args, char **argv, int line_number, char *line)
{
	int status;
	char *command_path;

	(void)line;

	if (args[0] == NULL)
		return (1);

	if (_strchr(args[0], '/') != NULL)
	{
		command_path = args[0];
		if (access(command_path, X_OK) != 0)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
				argv[0], line_number, args[0]);
			return (126);
		}
	}
	else
	{
		command_path = find_command_path(args[0]);
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n",
				argv[0], line_number, args[0]);
			return (127);
		}

		if (access(command_path, X_OK) != 0)
		{
			fprintf(stderr, "%s: %d: %s: Permission denied\n",
				argv[0], line_number, args[0]);
			free(command_path);
			return (126);
		}
	}

	status = launch_process(command_path, args);

	if (command_path != args[0])
		free(command_path);

	return (status);
}

/**
 * launch_process - Crée un processus fils pour exécuter une commande.
 * @path: Chemin absolu ou relatif de la commande à exécuter.
 * @args: Tableau d'arguments pour la commande.
 *
 * Return: Code de sortie du processus exécuté.
 */
int launch_process(char *path, char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		wait(&status);
	}

	return (WEXITSTATUS(status));
}
