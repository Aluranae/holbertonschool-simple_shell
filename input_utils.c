#include "main.h"
#include <stdlib.h> /* pour malloc, free */
#include <stdio.h> /* pour getline */
#include <string.h>
#include <stddef.h> /* pour NULL*/
#include <unistd.h> /* pour isatty, STDIN_FILENO */

/**
* split_line - Découpe une ligne de commande en tokens
* @line: Chaîne de caractères à découper
* @args: Tableau qui contiendra les pointeurs vers les tokens
*
* Cette fonction :
* - Utilise les espaces et retours à la ligne comme délimiteurs
* - Stocke chaque mot (token) dans le tableau args
* - Termine le tableau par NULL
*/

void split_line(char *line, char **args)
{
	char *token;

	int i = 0;

	/* 1. Extraire le premier token (séparé par espace ou retour à la ligne) */
	token = strtok(line, " \n");

	/* 2. Tant qu'il y a des tokens, les stocker dans le tableau args */
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}

	/* 3. Terminer le tableau avec NULL */
	args[i] = NULL;
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

	/* 4. Vérifier si l'entrée est interactive (isatty) */
	/*    Si oui, afficher le prompt "$ " avec write */
	if (isatty(STDIN_FILENO))
	{
	write(STDOUT_FILENO, "$ ", sizeof("$ ") - 1);
	}

	/* 5. Appeler getline() pour lire la ligne */
	/*    - Passer l'adresse de line et de n */
	/*    - Lire depuis stdin */
	input_lenght = getline(&line, &n, stdin);

	/* 6. Vérifier si getline a retourné -1 */
	/*    - Si oui, free(line) si nécessaire et retourner NULL */
	if (input_lenght == -1)
	{
		free(line);
		return (NULL);
	}

	/* 7. Retourner le pointeur line (ligne lue) */
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
