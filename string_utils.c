#include "main.h"
#include <stdlib.h>
#include <stddef.h>

/**
* _strchr - Locates the first occurrence of a character in a string
* @s: The string to search
* @c: The character to find
*
* Return: Pointer to the first occurrence of c in s, or NULL if not found
*/

char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
		{
			return (s + i);
		}
	}

	return (NULL);
}

/**
* _strcat - Concatenates two strings
* @dest: Destination string (must have enough space)
* @src: Source string to append
*
* Return: Pointer to dest
*/

char *_strcat(char *dest, const char *src)
{
	int i = 0;

	int j = 0;

	while (dest[i] != '\0')
	{
		i++;
	}
		while (src[j] != '\0')
		{
			dest[i] = src[j];
			i++;
			j++;
		}

	dest[i] = '\0';

	return (dest);
}

/**
* _strcmp - Compares two strings
* @s1: First string
* @s2: Second string
*
* Return: 0 if equal, a negative value if s1 < s2, a positive value if s1 > s2
*/

int _strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while (s1[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}

	return (s1[i] - s2[i]);
}

/**
* _strcpy - Copies a string, including the null byte, from src to dest
* @dest: Destination buffer
* @src: Source string
*
* Return: Pointer to dest
*/

char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
* _strdup - Returns a pointer to a newly allocated space in memory,
*           which contains a copy of the string given as a parameter
* @str: The source string to duplicate
*
* Return: Pointer to the duplicated string, or NULL if malloc fails
*/

char *_strdup(const char *str)
{
	int i = 0;

	int len = 0;

	char *ptr;

	if (str == NULL)
	{
	return (NULL);
	}

	while (str[len] != '\0')
	len++;

	ptr = malloc((len + 1) * sizeof(char));

	if (ptr == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < len; i++)
	ptr[i] = str[i];
	ptr[len] = '\0';

	return (ptr);
}
