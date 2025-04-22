#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
 * get_pid - Récupère le PID du processus actuel.
 * 
 * Return: Le PID du processus actuel.
 */
pid_t get_pid(void)
{
    pid_t pid = getpid();
    if (pid == -1) {
        perror("Error retrieving PID");
        exit(1);  /* Quitter en cas d'erreur */
    }
    return pid;
}
