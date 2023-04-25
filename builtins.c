#include "shell.h"
/**
 * builtin - Funtion that call the env or the exit
 *
 * @command: command a verificar
 * Return: Integer
 */
int builtin(char *command)
{
	if (str_compare(command, "exit", 4) == 0)
	{
		free(command);
		exit(EXIT_SUCCESS);
		return (1);
	} else if (str_compare(command, "env", 3) == 0)
	{
		print_env();
		free(command);
		return (1);
	} else
		return (0);
}

void continuePROM(int signal)
{
(void) signal;
write(STDIN_FILENO, "\n($)", 4);
}
