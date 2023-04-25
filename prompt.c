#include "main.h"

#define MAX_COMMAND 10

void prompt(char **av, char **env)
{
    char *str = NULL;
    int i, j, status;
    size_t n = 0;
    ssize_t num_char;
    char *argv[MAX_COMMAND];
    char *path, *cmd_path, *token;
    pid_t pid;
    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
        printf("$ ");
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

        path = getenv("PATH");
        j = 0;
        argv[j] = strtok(str, " ");
        while (argv[j] != NULL)
        {
            argv[++j] = strtok(NULL, " ");
        }
        pid = fork();
        if (pid == -1)
        {
            free(str);
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            if ((argv[0] == NULL) || strlen(argv[0]) == 0)
            {
                continue;
            }

            if (execve(argv[0], argv, env) == -1)
            { 
                token = strtok(path, ":");
                while (token != NULL)
                {
                    cmd_path = malloc(strlen(token) + strlen(argv[0]) + 2);
                    sprintf(cmd_path, "%s/%s", token, argv[0]);
                    if (access(cmd_path, F_OK) == 0)
                    {
                        argv[0] = cmd_path;
                        execve(argv [0], argv, env);
                    }
                    else
                    {
                        free(cmd_path);
                        token =strtok(NULL, ":");
                    }
                }
                printf("%s:command not found\n", av[0]);
                free(str);
                exit(127);
            }
            else if (execve(argv[0], argv, env) == -1)
            {
                printf("%s: No such file or directory\n", av[0]);
            }
            else
            {
                return;
            }
        }
        else
        {
            wait(&status);
        }
    }
}
