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
            exit(98);
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
        argv[j] = strtok(string, " ");
        while (argv[j] != NULL)
        {
            argv[++j] = strtok(NULL, " ");
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
            if ((argv[0] == NULL) || strlen(argv[0]) == 0)
            {
                free(string);
                exit(WEXITSTATUS(status));
            }
            if (execve(argv[0], argv, env) == -1)
            {
                cmd_path = malloc(strlen(argv[0]) + 1);
                if (cmd_path == NULL)
                {
                    free(string);
                    exit(EXIT_FAILURE);
                }
                token = strtok(path, ":");
                while (token != NULL)
                {
                    strcpy(cmd_path, token);
                    strcat(cmd_path, "/");
                    strcat(cmd_path, argv[0]);
                    execve(cmd_path, argv, env);
                    token = strtok(NULL, ":");
                }
                free(cmd_path);
                free(string);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, WUNTRACED);
            exit_status = WEXITSTATUS(status);
        }
    }
}