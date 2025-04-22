#include <stdlib.h>
#include <stdio.h>
/**
 * exit_shell - Quitte le shell proprement.
 * @command: La commande d'exécution (pour gérer des actions spécifiques si nécessaire).
 */
void exit_shell(char *command)
{
    (void)command;  /* Le paramètre n'est pas utilisé ici */
    exit(0);  /* Quitter le shell avec un code de succès */
}
