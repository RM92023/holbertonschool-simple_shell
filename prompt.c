#include "main.h"

#define MAX_COMMAND 10

extern char **environ;

void prompt(char **av, char **env)
{
    char *str = NULL;
    char *path;
    int i, j, status;
    int found;
    size_t n = 0;
    ssize_t num_char;
    char *argv[MAX_COMMAND];
    pid_t pid;

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("%s$ ", av[0]);
        }

        num_char = getline(&str, &n, stdin);

        if (num_char == -1)
        {
            free(str);
            exit(EXIT_SUCCESS);
        }

        i = 0;
        while (str[i])
        {
            if (str[i] == '\n')
            {
                str[i] = 0;
            }
            i++;
        }

        j = 0;
        argv[j] = strtok(str, " ");

        while (argv[j] != NULL)
        {
            argv[++j] = strtok(NULL, " ");
        }

        if ((argv[0] == NULL) || strlen(argv[0]) == 0)
        {
            continue;
        }

        path = NULL;
        found = 0;

        /* Check if the command is in the PATH */
        if (strchr(argv[0], '/') == NULL)
        {
            char *token = strtok(env[0], ":");

            while (token != NULL)
            {
                path = malloc(strlen(token) + strlen(argv[0]) + 2);
                sprintf(path, "%s/%s", token, argv[0]);

                if (access(path, X_OK) == 0)
                {
                    found = 1;
                    break;
                }

                free(path);
                path = NULL;
                token = strtok(NULL, ":");
            }
        }
        else if (access(argv[0], X_OK) == 0) /* Command is an absolute path */
        {
            found = 1;
            path = argv[0];
        }

        if (!found)
        {
            printf("%s: command not found\n", argv[0]);
            continue;
        }

        pid = fork();

        if (pid == -1)
        {
            free(str);
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execve(path, argv, environ) == -1)
            {
                printf("%s: command not found\n", argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(&status);
        }

        free(path);
        path = NULL;
    }
}
