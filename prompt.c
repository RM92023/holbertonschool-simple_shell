#include "main.h"

#define MAX_COMMAND 10

/**
 * execute_command - execute the command typed by the user
 *
 * @argv: array of command line arguments
 * @env: environment
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command(char **argv, char **env)
{
    char *path, *cmd_path, *token;
    int status;
    pid_t pid;

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return (-1);
    }
    if (pid == 0)
    {
        if ((argv[0] == NULL) || strlen(argv[0]) == 0)
            return (0);
        if (execve(argv[0], argv, env) == -1)
        {
            if (access(argv[0], F_OK) != 0)
            {
                path = getenv("PATH");
                token = strtok(path, ":");
                while (token != NULL)
                {
                    cmd_path = malloc(strlen(token) + strlen(argv[0]) + 2);
                    sprintf(cmd_path, "%s/%s", token, argv[0]);
                    if (access(cmd_path, F_OK) == 0)
                    {
                        argv[0] = cmd_path;
                        execve(argv[0], argv, env);
                        free(cmd_path);
                    }
                    else
                    {
                        free(cmd_path);
                        token = strtok(NULL, ":");
                    }
                }
                /* Print an error message if the command is not found */
                fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
                return (127);
            }
        }
        return (0);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (WIFEXITED(status))
        {
            return (WEXITSTATUS(status));
        }
        return (-1);
    }
}