#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "shell.h"

/**
 * main - Entry point of the shell program.
 * @argc: Argument count.
 * @argv: Argument vector.
 * @envp: Environment variables.
 *
 * Return: Always 0 (success).
 */
int main(int argc, char *argv[], char **envp)
{
    char *line_input = NULL;   /* Variable pour stocker la ligne d'entrée */
    char **args;               /* Tableau pour stocker les arguments */
    size_t buffer_size = 0;    /* Taille du tampon d'entrée */
    ssize_t input_length;      /* Longueur de l'entrée lue */
    pid_t process_pid;         /* PID du processus fils */
    int index = 0;             /* Index pour parcourir les arguments */

    (void)argc;
    (void)argv;

    while (1) /* Boucle principale du shell */
    {
        if (isatty(STDIN_FILENO))  /* Mode interactif : afficher un prompt */
            printf(">>> ");

        input_length = getline(&line_input, &buffer_size, stdin); /* Lire l'entrée */
        if (input_length == -1) /* Si Ctrl+D ou erreur */
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            break;
        }

        line_input[strcspn(line_input, "\n")] = '\0'; /* Supprimer le \n à la fin */

        args = malloc(sizeof(char*) * (input_length / 2 + 1)); /* Allouer de la mémoire */
        if (!args) /* Vérification de l'allocation */
        {
            perror("Erreur d'allocation");
            free(line_input);
            return 1;
        }

        index = 0;
        args[index] = strtok(line_input, " \t"); /* Séparer par espace/tabulation */
        while (args[index] != NULL)
            args[++index] = strtok(NULL, " \t");
        args[index] = NULL; /* Terminer la liste par NULL */

        if (args[0] == NULL) /* Ligne vide */
        {
            free(args);
            continue;
        }

        if (handle_builtin(args, envp)) /* Commande interne */
        {
            free(args);
            continue;
        }

        process_pid = fork(); /* Créer un processus fils */
        if (process_pid == 0) /* Processus fils */
        {
            if (execve(args[0], args, envp) == -1) /* Exécution de la commande */
            {
                perror("Erreur d'exécution");
                free(args);
                exit(127); /* Code d'erreur */
            }
        }
        else if (process_pid > 0) /* Processus parent */
        {
            wait(NULL); /* Attendre la fin du fils */
        }
        else /* Erreur de fork */
        {
            perror("Erreur de fork");
        }

        free(args); /* Libérer les arguments */
    }

    free(line_input); /* Libérer la ligne d'entrée */
    return 0;
}
