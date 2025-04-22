#include "main.h"
#include <stdlib.h>		/* Pour exit et free */
#include <unistd.h>     /* Pour write() */
#include <stddef.h>     /* Pour NULL */
#include <string.h>     /* Pour _strlen() si besoin */
#include <stdio.h>

/**
* handle_exit - Vérifie si la commande est "exit"
*               et quitte proprement le shell si c’est le cas
* @args: Tableau de tokens
* @line: Ligne lue à libérer avant de quitter
*
* Return: 1 si le shell doit se fermer, 0 sinon
*/

int handle_exit(char **args, char *line)
{
	/* 1. Vérifier si le premier token est NULL (aucune commande tapée) */
	/*    - Si oui, retourner 0 */
	if (args[0] == NULL)
		return (0);

	/* 2. Comparer le premier token avec "exit" */
	/*    - Utiliser _strcmp() pour tester l'égalité */
	if (_strcmp(args[0], "exit") == 0)
	{
		/* 3. Si c’est "exit" */
		/* 3a. Libérer la ligne lue */
		free(line);

		/* 3b. Quitter proprement */
		exit(0);
	}

	/* 4. Si ce n’est pas "exit", retourner 0 */
	return (0);
}


/**
* handle_env - Affiche toutes les variables d’environnement
* @args: Tableau de tokens (args[0] est supposé être "env")
* @line: Ligne d’entrée (non utilisée dans cette fonction)
*
* Return: 1 si "env" a été reconnu et traité, 0 sinon
*/

int handle_env(char **args, char *line)
{
	/* 1. Déclarer un index entier pour parcourir les variables */
	int i = 0;

	(void)line;

	/* 2. Vérifier si le premier token est NULL (aucune commande tapée) */
	if (args[0] == NULL)
		return (0);

	/* 3. Comparer le premier token avec "env" */
	if (_strcmp(args[0], "env") == 0)
	{
		/* 4a. Parcourir le tableau environ jusqu'à NULL */
		while (environ[i] != NULL)
		{
			/* 4b. Afficher chaque variable d'environnement */
			printf("%s\n", environ[i]);
			i++;
		}
		return (1);
	}
	return (0);
}


/**
* handle_builtin - Vérifie si la commande est un builtin (env, exit, etc.)
*                  et appelle la fonction associée
* @args: Le tableau de tokens (arguments de la commande)
* @line: La ligne complète à libérer si besoin (utile pour "exit")
*
* Return: 1 si la commande est un builtin et a été exécutée, 0 sinon
*/

int handle_builtin(char **args, char *line)
{
	/* 1. Déclarer une variable d’index (ex: int i = 0) */

	int i = 0;

	/* 2. Définir un tableau de structures builtin_t */
	/*    - Chaque élément contient le nom de la commande interne */
	/*    - Et un pointeur vers sa fonction correspondante */
	builtin_t builtins[] = {
		{"exit", handle_exit},
		{"env", handle_env},
		{NULL, NULL}
	};

	/* 3. Vérifier si args[0] est NULL */
	/*    - Si oui, retourner 0 */
	if (args[0] == NULL)
		return (0);

	/* 4. Parcourir le tableau des builtins */
	/*    - Pour chaque élément : */
	while (builtins[i].name != NULL)
	{
		/* 4a. Comparer args[0] avec builtin[i].name (avec _strcmp) */
		if (_strcmp(args[0], builtins[i].name) == 0)
		{
			/* 4b. Si c’est égal, exécuter la fonction associée builtin[i].func */
			builtins[i].func(args, line);

			/* 4c. Retourner 1 (commande interne exécutée) */
			return (1);
		}
		i++;
	}
	/* 5. Si aucune correspondance trouvée, retourner 0 */
	return (0);
}
