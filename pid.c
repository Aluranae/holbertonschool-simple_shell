#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
/**
 * get_pid - Récupère le PID du processus actuel.
 * 
 * Return: Le PID du processus actuel.
 */
pid_t get_pid(void)
{
    return getpid();  /* Retourne le PID du processus actuel */
}
