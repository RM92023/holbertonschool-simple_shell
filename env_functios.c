#include "shell.h"
/**
 * _getenv - Function that get the PATH from env
 * @name: pointer to string - name
 * Return: On succes return the NULL if it fails
 */
char *_getenv(const char *name)
{
	int l = str_lenght((char *)name);
	char **env = environ;

	while (*env != NULL)
	{
	if (str_compare(*env, (char *)name, l) == 0 && env[0][l] == '=')
	return (*env + l + 1);
		env++;
	}
	return (NULL);
}

/**
 * print_env - Funtion that prints the env
 * using the environ
 * Return: Nothing
 */

int print_env(void)
{
	char **env = environ;
	int i = 0;

	while (env[i])
	{
		write(1, env[i], str_lenght(env[i]));
		write(1, "\n", 1);
		++i;
	}
	return (1);
}
