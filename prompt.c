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
    int line_num = 1;

    pid_t pid;

    /* Agregar path del directorio actual al comienzo de PATH */
    char *current_dir = getcwd(NULL, 0);
    char *new_path = malloc(strlen(current_dir) + strlen(getenv("PATH")) + 2);
    sprintf(new_path, "%s:%s", current_dir, getenv("PATH"));
    setenv("PATH", new_path, 1);
    free(current_dir);
    free(new_path);

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
            j++;
            argv[j] = strtok(NULL, " ");
        }
        argv[j] = NULL; /* Asegurarse de que el último elemento sea NULL. */
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
                fprintf(stderr, "%s: %d: %s: not found\n", av[0], line_num, argv[0]);
                free(str);
                exit(127); /* Comando no encontrado */
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
