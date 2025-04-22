#include "main.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
* is_executable - Vérifie si un fichier est exécutable.
* @path: Chemin de la commande.
* @argv: argv[0] pour le message d'erreur.
* @line_number: Numéro de ligne pour affichage.
* @cmd_name: Nom réel de la commande (args[0]).
*
* Return: 0 si exécutable, 126 sinon.
*/

int is_executable(char *path, char **argv, int line_number, char *cmd_name)
{
	if (access(path, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
			argv[0], line_number, cmd_name);
		return (126);
	}
	return (0);
}

/**
* launch_process - Lance le processus avec fork + execve.
* @command_path: Chemin complet de la commande.
* @args: Commande tokenisée.
*
* Return: Code de sortie de la commande.
*/

int launch_process(char *command_path, char **args)
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
		if (execve(command_path, args, environ) == -1)
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

/**
 * execute_command - Exécute une commande avec ou sans PATH.
 * @args: Commande tokenisée.
 * @argv: argv[0] pour les messages d'erreur.
 * @line_number: Numéro de ligne pour les erreurs.
 * @line: Ligne brute de l'utilisateur (non utilisée ici).
 *
 * Return: Code d'exécution (0, 1, 126, 127).
 */

int execute_command(char **args, char **argv, int line_number, char *line)
{
	char *command_path;
	int exec_check;

	(void)line;

	if (args[0] == NULL)
		return (1);

	if (_strchr(args[0], '/') != NULL)
	{
		command_path = args[0];
		exec_check = is_executable(command_path, argv, line_number, args[0]);
		if (exec_check != 0)
			return (exec_check);
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
		exec_check = is_executable(command_path, argv, line_number, args[0]);
		if (exec_check != 0)
		{
			free(command_path);
			return (exec_check);
		}
	}

	exec_check = launch_process(command_path, args);

	if (command_path != args[0])
		free(command_path);

	return (exec_check);
}
