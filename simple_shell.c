#include <stdio.h>      /* Pour printf, perror, getline */
#include <stdlib.h>     /* Pour malloc, free, exit */
#include <string.h>     /* Pour strtok, strcmp, strcspn */
#include <unistd.h>     /* Pour fork, execve, chdir, isatty */
#include <sys/types.h>  /* Pour pid_t */
#include <sys/wait.h>   /* Pour wait */
#include "shell.h"      /* Pour exit_shell, print_env, get_pid */

/**
 * main - Point d'entrée du programme shell.
 * @argc: Nombre d'arguments.
 * @argv: Tableau d'arguments.
 * @envp: Variables d'environnement.
 *
 * Return: 0 en cas de succès.
 */
int main(int argc, char *argv[], char **envp)
{
	char *line_input = NULL;
	char **args;
	size_t buffer_size = 0;
	ssize_t input_length;
	pid_t process_pid;
	int index = 0;

	(void)argc;
	(void)argv;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(">>> "); /* Affiche un prompt */

		input_length = getline(&line_input, &buffer_size, stdin);
		if (input_length == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line_input[strcspn(line_input, "\n")] = '\0'; /* Supprime le \n final */

		args = malloc(sizeof(char *) * (input_length / 2 + 1));
		if (!args)
		{
			perror("Erreur d'allocation");
			free(line_input);
			return (1);
		}

		index = 0;
		args[index] = strtok(line_input, " \t");
		while (args[index] != NULL)
			args[++index] = strtok(NULL, " \t");
		args[index] = NULL;

		if (args[0] == NULL)
		{
			free(args);
			continue;
		}

		/* Commandes internes */
		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			exit_shell(NULL);
		}
		else if (strcmp(args[0], "cd") == 0)
		{
			if (args[1] == NULL)
				fprintf(stderr, "cd: argument manquant\n");
			else if (chdir(args[1]) != 0)
				perror("cd");
			free(args);
			continue;
		}
		else if (strcmp(args[0], "env") == 0)
		{
			print_env(envp);
			free(args);
			continue;
		}
		else if (strcmp(args[0], "pid") == 0)
		{
			printf("PID actuel : %d\n", get_pid());
			free(args);
			continue;
		}

		/* Processus fils pour exécuter la commande */
		process_pid = fork();
		if (process_pid == 0)
		{
			if (execve(args[0], args, envp) == -1)
			{
				perror("Erreur d'exécution");
				free(args);
				exit(127);
			}
		}
		else if (process_pid > 0)
		{
			wait(NULL);
		}
		else
		{
			perror("Erreur de fork");
		}

		free(args);
	}

	free(line_input);
	return (0);
}
