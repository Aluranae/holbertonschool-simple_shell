#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include "shell.h"

/* Fonction pour obtenir le PID du processus actuel */
pid_t get_pid(void)
{
    return getpid();  /* Retourne le PID du processus actuel */
}

/* Fonction pour quitter le shell */
void exit_shell(char *command)
{
    (void)command;  /* Argument non utilisé dans cette fonction */
    exit(0);  /* Quitte le shell avec un code de succès */
}

/* Fonction pour afficher les variables d'environnement */
int print_env(char **env)
{
    int i = 0;

    while (env[i] != NULL)  /* Parcours des variables d'environnement */
    {
        printf("%s\n", env[i]);  /* Affiche chaque variable d'environnement */
        i++;
    }

    return 0;  /* Retourne 0 (succès) */
}

/**
 * main - Point d'entrée du programme shell.
 * @argc: Compteur d'arguments.
 * @argv: Tableau d'arguments.
 * @envp: Variables d'environnement.
 *
 * Return: Toujours 0 (succès).
 */
int main(int argc, char *argv[], char **envp)
{
    char *line_input = NULL;   /* Variable pour stocker la ligne d'entrée */
    char **args;               /* Tableau pour stocker les arguments */
    size_t buffer_size = 0;    /* Taille du tampon d'entrée */
    ssize_t input_length;      /* Longueur de l'entrée lue */
    pid_t process_pid;         /* PID du processus fils */
    int index = 0;             /* Index pour parcourir les arguments */

    (void)argc;  /* Les arguments ne sont pas utilisés dans cette fonction */
    (void)argv;

    while (1)  /* Boucle principale du shell */
    {
        if (isatty(STDIN_FILENO))  /* Mode interactif (si le shell est lancé dans un terminal) */
            printf(">>> ");        /* Affichage du prompt */

        input_length = getline(&line_input, &buffer_size, stdin);  /* Lecture de l'entrée de l'utilisateur */
        if (input_length == -1)  /* Si on atteint la fin du fichier (Ctrl+D) */
        {
            if (isatty(STDIN_FILENO))
                printf("\n");  /* Ajouter une nouvelle ligne avant de quitter */
            break;  /* Sortir de la boucle et du shell */
        }

        line_input[strcspn(line_input, "\n")] = '\0';  /* Supprimer le caractère de nouvelle ligne à la fin de la commande */

        args = malloc(sizeof(char*) * (input_length / 2 + 1));  /* Allocation dynamique de mémoire pour les arguments */
        if (!args)  /* Si l'allocation échoue */
        {
            perror("Erreur d'allocation");
            free(line_input);
            return 1;
        }

        index = 0;
        args[index] = strtok(line_input, " \t");  /* Découper la ligne d'entrée par espaces ou tabulations */
        while (args[index] != NULL)  /* Parcourir les arguments et les ajouter au tableau */
            args[++index] = strtok(NULL, " \t");
        args[index] = NULL;  /* Terminer la liste des arguments avec NULL */

        if (args[0] == NULL)  /* Si la ligne est vide (pas de commande), on continue */
        {
            free(args);  /* Libérer la mémoire allouée pour les arguments */
            continue;
        }

        /* Gestion des commandes internes */
        if (strcmp(args[0], "exit") == 0)  /* Si la commande est "exit" */
        {
            free(args);  /* Libérer la mémoire allouée pour les arguments */
            exit_shell(NULL);  /* Quitter le shell */
        }
        else if (strcmp(args[0], "cd") == 0)  /* Si la commande est "cd" (changer de répertoire) */
        {
            if (args[1] == NULL)  /* Si l'argument est manquant */
            {
                fprintf(stderr, "cd: argument manquant\n");
            }
            else if (chdir(args[1]) != 0)  /* Si l'appel à chdir échoue */
            {
                perror("cd");
            }
            free(args);  /* Libérer la mémoire allouée pour les arguments */
            continue;    /* Recommencer la boucle pour afficher le prompt */
        }
        else if (strcmp(args[0], "env") == 0)  /* Si la commande est "env" (afficher les variables d'environnement) */
        {
            print_env(envp);  /* Appeler la fonction pour afficher les variables d'environnement */
            free(args);  /* Libérer la mémoire allouée pour les arguments */
            continue;    /* Recommencer la boucle pour afficher le prompt */
        }
        else if (strcmp(args[0], "pid") == 0)  /* Commande "pid" */
        {
            printf("PID actuel : %d\n", get_pid());  /* Affiche PID */
            free(args);
            continue;
        }

        /* Création d'un processus fils pour exécuter la commande */
        process_pid = fork();  /* Créer un processus fils */
        if (process_pid == 0)  /* Si c'est le processus fils */
        {
            if (execve(args[0], args, envp) == -1)  /* Si execve échoue */
            {
                perror("Erreur d'exécution");
                free(args);  /* Libérer la mémoire allouée pour les arguments */
                exit(127);  /* Quitter le processus fils avec un code d'erreur */
            }
        }
        else if (process_pid > 0)  /* Si c'est le processus parent */
        {
            wait(NULL);  /* Attendre la fin du processus fils */
        }
        else  /* Si fork échoue */
        {
            perror("Erreur de fork");
        }

        free(args);  /* Libérer la mémoire allouée pour les arguments après l'exécution */
    }

    free(line_input);  /* Libérer la mémoire allouée pour la ligne d'entrée */
    return 0;  /* Terminer le programme */
}
