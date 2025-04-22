#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/**
* main - Entry point of the shell program
* @argc: Argument count
* @argv: Argument vector
*
* Return: Exit status of the shell
*/

int main(int argc, char **argv)
{
	(void)argc;
	return (core_shell(argv));
}
