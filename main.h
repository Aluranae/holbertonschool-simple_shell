#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdlib.h>

/* Variable globale d'envrionnement */

extern char **environ;

/* Structur pour Builtin */

/**
* struct builtin_s - Structure représentant une commande interne (builtin)
* @name: Le nom de la commande (ex: "exit", "env", etc.)
* @func: Pointeur vers la fonction associée à cette commande
*
* Cette structure permet de lier le nom d'une commande interne à la fonction
* correspondante qui doit être exécutée. Elle est utilisée pour parcourir
* facilement la liste des commandes internes disponibles dans le shell.
*/

typedef struct builtin_s
{
	char *name;
	int (*func)(char **args, char *line);
} builtin_t;


/* Fonctions gestion de l'input */

char **split_line(char *line);
char *read_input(void);
int is_line_empty(const char *line);
void free_args(char **args);

/* Fonctions variables d'environnement */

char *_getenv(const char *name);
char *find_command_path(char *command);

/* Fonctions du shell */

int handle_exit(char **args, char *line);
int handle_env(char **args, char *line);
int handle_builtin(char **args, char *line);
int execute_command(char **args, char **argv, int line_number, char *line);
int launch_process(char *path, char **args);
int is_executable(char *path, char **argv, int line_number, char *cmd_name);


int core_shell(char **argv);

/* Fonctions gestions strings */

unsigned int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strdup(const char *str);
char *_strchr(char *s, char c);



#endif /* MAIN_H */
