#include "main.h"

#define MAX_COMMAND 10

void prompt(char **av, char **env)
{
    char *str = NULL;
    int i, j, status;
    size_t n = 0;
    ssize_t num_char;
    char *argv[MAX_COMMAND];
    pid_t pid;

    char *cmd_path;

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

        /* Ignore empty lines and leading/trailing spaces */
        if (strcmp(str, "\n") == 0 || strspn(str, " \t\n") == strlen(str))
        {
            continue;
        }

        j = 0;
        argv[j] = strtok(str, " ");
        while (argv[j] != NULL)
        {
            argv[++j] = strtok(NULL, " ");
        }

        /* Check if command exists */
        if (access(argv[0], F_OK) == -1)
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
            /* Set PATH to empty string */
            putenv("PATH=");

            /* Remove all environment variables */
            clearenv();

            /* Remove PATH variable and set PATH1 variable */
            unsetenv("PATH");
            setenv("PATH1", "/bin:/usr/bin", 1);

            /*if ((argv[0] == NULL) || strlen(argv[0]) == 0)
                {
                    continue;
                }
            else*/ if (execve(argv[0], argv, env) == -1)
            {
                cmd_path = search_command(argv[0], env);
                if (cmd_path == NULL)
                {
                    printf("%s: command not found\n", av[0]);
                    free(str);
                    exit(EXIT_FAILURE);
                }
                else
                {
                    if (execve(cmd_path, argv, env) == -1)
                    {
                        printf("%s: command not found\n", av[0]);
                        free(str);
                        free(cmd_path);
                        exit(EXIT_FAILURE);
                    }
                    free(cmd_path);
                }
            }
        }
        else
        {
            wait(&status);
        }
    }
}
