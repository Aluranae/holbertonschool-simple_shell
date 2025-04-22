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
