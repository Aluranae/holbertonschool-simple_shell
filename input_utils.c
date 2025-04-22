#include "main.h"
#include <stdlib.h> /* pour malloc, free */
#include <stdio.h> /* pour getline */
#include <string.h>
#include <stddef.h> /* pour NULL*/
#include <unistd.h> /* pour isatty, STDIN_FILENO */

#define MAX_ARGS 64  /* Nombre maximal d'arguments pris en charge */

/**
* split_line - Découpe une ligne de commande en tokens (mots)
* @line: Chaîne de caractères à analyser (modifiée par strtok)
*
* Cette fonction :
* - Alloue dynamiquement un tableau de chaînes de caractères (char **)
* - Utilise strtok pour découper la ligne en fonction des espaces
*   et sauts de ligne
* - Remplit le tableau avec chaque mot (token)
* - Termine le tableau par un pointeur NULL, compatible avec execve
*
* Return: Un tableau de pointeurs vers les tokens, ou NULL si échec
*/

char **split_line(char *line)
{
	char **args;
	char *token;
	int i = 0;

	/* Allouer de l'espace pour MAX_ARGS pointeurs */
	args = malloc(sizeof(char *) * MAX_ARGS);
	if (args == NULL)
		return (NULL);

	/* Extrait le premier mot (token) séparé par espace ou retour à la ligne */
	token = strtok(line, " \n");

	/* Tant qu'on trouve des tokens, les stocker dans le tableau */
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}

	/* Terminer le tableau par NULL pour compatibilité execve */
	args[i] = NULL;

	return (args);
}

/**
* read_input - Lit une ligne depuis l'entrée standard
*             Affiche un prompt si en mode interactif.
*
* Return: Pointeur vers la ligne lue (à free après usage), ou NULL si EOF
*/


char *read_input(void)
{
	/* 1. Déclarer un pointeur char *line initialisé à NULL */
	char *line = NULL;

	/* 2. Déclarer une variable size_t n initialisée à 0 */
	/* Taille du buffer alloué par getline (initialement 0, */
	/* réajustée automatiquement si nécessaire) */
	size_t n = 0;

	/* 3. Déclarer une variable ssize_t pour stocker */
	/*    la valeur de retour de getline */
	/* Longueur de la ligne lue par getline, ou -1 si EOF/erreur */
	ssize_t input_lenght = 0;

	/* 4. Appeler getline() pour lire la ligne */
	/*    - Passer l'adresse de line et de n */
	/*    - Lire depuis stdin */
	input_lenght = getline(&line, &n, stdin);

	/* 5. Vérifier si getline a retourné -1 */
	/*    - Si oui, free(line) si nécessaire et retourner NULL */
	if (input_lenght == -1)
	{
		free(line);
		return (NULL);
	}

	/* 6. Retourner le pointeur line (ligne lue) */
	return (line);
}


/**
* is_line_empty - Vérifie si une ligne est vide ou composée uniquement
*                 d'espaces et/ou de tabulations
* @line: La chaîne de caractères à analyser
*
* Return: 1 si la ligne est vide ou inutile, 0 sinon
*/

int is_line_empty(const char *line)
{
	/* 1. Déclarer un index entier i */
	int i = 0;

	/* 2. Parcourir chaque caractère de la ligne */
	/*    - Tant que le caractère courant n'est pas '\0' */
	/*    - À chaque itération : */
	/* 2a. Vérifier si le caractère courant n’est pas un espace */
		/*     ni une tabulation */
		/*     - Si c’est un caractère "utile", retourner 0 (ligne non vide) */

		/* 2b. Sinon, continuer à avancer dans la ligne */
	while (line[i] != '\0')
	{
		if (line[i] == '\t' || line[i] == ' ' || line[i] == '\n')
		{
			i++;
		}
		else
		{
			return (0);
		}
	}

	/* 3. Si la boucle se termine sans rencontrer de caractère utile */
	/* 4. Retourner 1 pour indiquer que la ligne est vide ou inutile */
	return (1);
}

/**
* free_args - Libère la mémoire allouée pour un tableau de chaînes
* @args: Tableau de pointeurs à libérer
*
* Cette fonction libère la mémoire allouée dynamiquement pour un tableau
* de chaînes de caractères, si celui-ci n'est pas NULL.
*/

void free_args(char **args)
{
	if (args)
		free(args);
}
