#include "main.h"

#define MAX_COMMAND 10

void prompt(char **av, char **env, int interactive)
{
    char *str = NULL;
    int i, j, status;
    size_t n = 0;
    ssize_t num_char;
    char *argv[MAX_COMMAND];
    pid_t pid;
    while (1)
    {
        if (interactive && isatty(STDIN_FILENO))
        {
            printf("$ ");
        }

        if (!interactive)
        {
            num_char = getline(&str, &n, stdin);
            if (num_char == -1)
            {
                free(str);
                exit(EXIT_SUCCESS);
            }
        }
        else
        {
            num_char = getline(&str, &n, stdin);
            if (num_char == -1)
            {
                if (interactive)
                {
                    printf("\n");
                }
                free(str);
                break;
            }
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
            else
            {
                char *cmd = basename(argv[0]);
                char cmd_path[256];
                if (access(cmd, X_OK) == 0)
                {
                    strcpy(cmd_path, cmd);
                }
                else
                {
                    sprintf(cmd_path, "/bin/%s", cmd);
                }
                if (execve(cmd_path, argv, env) == -1)
                {
                    printf("%s: No such file or directory\n", av[0]);
                }
            }
        }
        else
        {
            wait(&status);
        }
    }
}
