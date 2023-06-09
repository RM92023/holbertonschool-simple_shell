#include "main.h"

#define MAX_COMMAND 10

void prompt(char **av __attribute__((unused)), char **env)
{
    char *string = NULL;
    int i, j, status, exit_status = 0;
    size_t n = 0;
    ssize_t len;
    char *argv[MAX_COMMAND];
    char *path, *cmd_path, *token;
    char **ptr;
    pid_t pid;
    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("$ ");
            fflush(stdout);
        }
        len = getline(&string, &n, stdin);
        if (len == -1)
        {
            free(string);
            exit(WEXITSTATUS(status));
        }
        i = 0;
        while (string[i])
        {
            if (string[i] == '\n')
            {
                string[i] = 0;
            }
            i++;
        }
        path = getenv("PATH");
        j = 0;
        argv[j] = strtok(string, " \t\n\v\f\r");
        while (argv[j] != NULL)
        {
            argv[++j] = strtok(NULL, " \t\n\v\f\r");
        }
        if (strcmp(argv[0], "clear") == 0)
        {
            system("clear");
            continue;
        }
        if (strcmp(argv[0], "exit") == 0)
        {
            free(string);
            exit(exit_status);
        }
        if (strcmp(argv[0], "env") == 0)
        {
            ptr = env;
            while (*ptr != NULL)
            {
                printf("%s\n", *ptr);
                ptr++;
            }
            continue;
        }
        pid = fork();
        if (pid == -1)
        {
            free(string);
            exit(WEXITSTATUS(status));
        }
        if (pid == 0)
        {
            if (execve(argv[0], argv, env) == -1)
            {
                if (path != NULL)
                {
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
                }

                /* Print an error message if the command is not found */
                fprintf(stderr, "./hsh: 1: %s: not found\n", argv[0]);
                free(string);
                exit(127);
                
                if ((argv[0] == NULL) || strlen(argv[0]) == 0)
                {
                    free(string);
                    exit(WEXITSTATUS(status));
                }
            }
        }
        else
        {
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
            {
                exit_status = WEXITSTATUS(status);
            }
        }
        free(string);
        string = NULL;
    }
}
