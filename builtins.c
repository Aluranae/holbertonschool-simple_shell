#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

/* Fonction pour obtenir le PID du processus actuel */
pid_t get_pid(void)
{
    return getpid();  /* Retourne le PID du processus actuel */
}

/* Fonction pour quitter le shell */
void exit_shell(char *command)
{
    (void)command;
    exit(0);
}

/* Fonction pour afficher les variables d'environnement */
int print_env(char **env)
{
    int i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return 0;
}

/**
 * handle_builtin - Gère les commandes internes du shell.
 * @args: Commandes et arguments.
 * @env: Variables d'environnement.
 * Return: 1 si une commande interne est exécutée, 0 sinon.
 */
int handle_builtin(char **args, char **env)
{
    if (strcmp(args[0], "exit") == 0) /* Commande "exit" */
    {
        exit_shell(NULL);
    }
    else if (strcmp(args[0], "cd") == 0) /* Commande "cd" */
    {
        if (args[1] == NULL) /* Aucun argument */
        {
            fprintf(stderr, "cd: argument manquant\n");
        }
        else if (chdir(args[1]) != 0) /* Erreur de chdir */
        {
            perror("cd");
        }
        return 1;
    }
    else if (strcmp(args[0], "env") == 0) /* Commande "env" */
    {
        print_env(env);
        return 1;
    }
    else if (strcmp(args[0], "pid") == 0) /* Commande "pid" */
    {
        printf("PID actuel : %d\n", get_pid());
        return 1;
    }

    return 0; /* Pas une commande interne */
}
