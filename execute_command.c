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

	/* vérifi si la ligne est vide */
	/* (ex : l'utilisateur a juste appuyé sur Entrée) */
	if (args[0] == NULL)
		return (1); /* Ne rien faire, simplement réafficher le prompt */

	/* vérifier si c'est une commande interne (builtin comme "exit" ou "env")*/
	if (handle_builtin(args, line) == 1)
		return (0); /* La commande builtin a été traitée avec succès */

	/* chercher le chemin complet de la commande dans la variable PATH */
	path = find_command_path(args[0]);
	if (!path)
	{
		/* Si la commande n’est pas trouvée, afficher une erreur */
		/* avec le numéro de ligne */
		fprintf(stderr, "%s: %d: %s: not found\n", argv[0], line_number, args[0]);
		return (0); /* Code de retour standard pour "commande introuvable" */
	}

	/* vérifier les permissions d’exécution du fichier trouvé */
	if (access(path, X_OK) != 0)
	{
		fprintf(stderr, "%s: %d: %s: Permission denied\n",
			argv[0], line_number, args[0]);
		free(path);
		return (126); /* Code de retour standard pour "permission refusée" */
	}

	/* lancer le processus (fork + execve) */
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

	/* créer un nouveau processus avec fork() */
	pid = fork();

	if (pid == 0)
	{
		/* Cas du processus enfant : exécuter la commande */
		execve(path, args, environ);

		/* Si execve échoue, afficher l’erreur */
		perror("execve");

		/* Libérer le chemin puis quitter l’enfant avec un code d’erreur */
		free(path);
		exit(1);
	}
	else if (pid > 0)
	{
		/* Cas du processus parent : attendre la fin de l’enfant */
		wait(&status);
	}
	else
	{
		/* fork() a échoué */
		perror("fork");
	}

	/* Libérer la mémoire allouée pour le chemin après l’exécution */
	free(path);

	return (1); /* Retourne 1 pour indiquer que le shell peut continuer */
}
