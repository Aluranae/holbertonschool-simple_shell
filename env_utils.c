#include "main.h"       /* Pour le prototype et extern environ */
#include <stddef.h>     /* Pour NULL */
#include <string.h>     /* Pour _strcmp ou _strncmp si besoin */
#include <stdlib.h>		/* Pour strtok, strdup, malloc, free */
#include <unistd.h>		/* Pour access */
#include <stdio.h>

/**
* _getenv - Récupère la valeur d’une variable d’environnement
* @name: Le nom de la variable recherchée (ex: "PATH")
*
* Return: Un pointeur vers la valeur (après le =) si trouvée, NULL sinon
*/

char *_getenv(const char *name)
{
	/* 1. Déclarer les variables nécessaires */
	int i = 0;

	char *ptr;

	size_t len;

	/* 2. Vérifier que name n’est pas NULL */
	/*    - Si NULL, retourner NULL directement */
	if (name == NULL)
	{
		return (NULL);
	}

	/* 2bis. Calculer la longueur du nom cherché (name) */
		len = _strlen(name);

	/* 3. Parcourir le tableau global environ[] jusqu’à NULL */
	/*    - Pour chaque chaîne d’environnement */
	while (environ[i] != NULL)
	{
	/* 3a. Comparer les premiers caractères avec name */
	/*     - Utiliser _strncmp(environ[i], name, len) */
	/*     - Puis vérifier que le caractère suivant est '=' */
	if (_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		{
		/* 3b. Si correspondance trouvée : */
		/*     - Retourner un pointeur vers le caractère après '=' */
		ptr = &environ[i][len + 1];
		return (ptr);
		}
	i++;
	}
	/* 4. Si aucune correspondance, retourner NULL */
	return (NULL);
}


/**
* find_command_path - Cherche le chemin absolu d'une commande
* dans les dossiers du PATH
* @command: Nom de la commande à chercher (ex: "ls")
*
* Return: Une chaîne allouée avec le chemin complet si trouvé, NULL sinon
*/

char *find_command_path(char *command)
{
	char *path, *path_copy, *dir, *full_path;
	size_t path_len;

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);

	path_copy = _strdup(path);
	if (path_copy == NULL)
		return (NULL);

	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		path_len = _strlen(dir) + _strlen(command) + 2;
		full_path = malloc(path_len * sizeof(char));
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		_strcpy(full_path, dir);
		_strcat(full_path, "/");
		_strcat(full_path, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path); /* trouvé ! */
		}

		free(full_path);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* non trouvé */
}
