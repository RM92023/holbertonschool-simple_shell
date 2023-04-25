#include "shell.h"

/**
 * pathfinder -Funtion that find the PATH where the command is save
 * @command: Pointer - Command to find the path
 * Return: the PATH with the command to execute*
 */

char *pathfinder(char *command)
{
	char *path = NULL, *ctoprint = NULL;
	struct stat stats;
	char *token = NULL, *auxpath = NULL;
	int i = 0;
	/*char *c_source;*/

	if (stat(command, &stats) == 0)
		return (command);
	path = _getenv("PATH");
	auxpath = malloc(strlen(path) + 1);
	auxpath = strcpy(auxpath, path);
	token = strtok(auxpath, ":\n");
	command = str_concat("/", command);
	/*printf("desde el pathfinder [%s]",command);*/
	/*
	*stat() return 0 on successful
	*returns -1 if its unable to get file
	*properties
	*/
	while (token != NULL)
	{
		ctoprint = str_concat(token, command);

		if (stat(ctoprint, &stats) == 0)
		{
			free(command);
			free(auxpath);
			return (ctoprint);
		}
		free(ctoprint);
		/*revisar uqe hace strtok con null*/
		token = strtok(NULL, ":\n");
		i++;
	}
	/*printf("\ncommand a ejecutar: %s", ctoprint);*/
	free(command);
	free(auxpath);
	return (NULL);
}
