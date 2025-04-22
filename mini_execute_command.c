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
 * Return: 1 pour continuer la boucle du shell, ou 127 si erreur.
 */
int execute_command(char **args, char **argv, int line_number, char *line)
{
	pid_t pid;
	int status;
	char *command_path;

	(void)line;

	/* Étape 1 : Vérifier si la commande est vide */
	if (args[0] == NULL)
		return (1);

	if (access(args[0], X_OK) == 0)
	{
		command_path = args[0];
	}
	else
	{
		command_path = find_command_path(args[0]);
		if (command_path == NULL)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_number, args[0]);
			return (127);
		}
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		if (command_path != args[0])
			free(command_path);
		return (1);
	}

	/* Étape 5 : Dans le fils, exécuter la commande */
	if (pid == 0)
	{
		if (execve(command_path, args, environ) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		/* Étape 6 : Attendre la fin du processus fils */
		wait(&status);
	}

	/* Étape 7 : Libérer le chemin alloué si nécessaire */
	if (command_path != args[0])
		free(command_path);

	/* Étape 8 : Retourner 1 pour continuer la boucle du shell */
	return (WEXITSTATUS(status));
}
