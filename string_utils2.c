#include "main.h"
#include <stdlib.h>
#include <stddef.h>

/**
* _strlen - Returns the length of a string
* @s: The string to measure
*
* Return: The number of characters in the string (excluding '\0')
*/

unsigned int _strlen(const char *s)
{
	int i = 0;

	while (s[i] != '\0')
	i++;

	return (i);
}

/**
* _strncmp - Compares two strings up to n characters
* @s1: The first string
* @s2: The second string
* @n: The maximum number of characters to compare
*
* Return: 0 if the strings are equal, a positive or negative value
*         depending on the lexicographical order of the strings.
*/

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i = 0;

	while (i < n && s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}

	if (i < n)
		return (s1[i] - s2[i]);

	return (0);
}
