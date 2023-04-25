#include "main.h"

#define MAX_COMMAND 10
#define MAX_PATH_LENGTH 1024

void prompt(char **av, char **env)
{
    char *str = NULL;
    char *dir;
    int found = 0;
    int i, j, status;
    size_t n = 0;
    ssize_t num_char;
    char *argv[MAX_COMMAND];
    pid_t pid;
    char *path = getenv("PATH");
    char *directories[MAX_COMMAND];
    int num_directories = 0;
    char path_copy[MAX_PATH_LENGTH];
    char cwd[MAX_PATH_LENGTH];
    (void)av;

    /* Parse PATH variable */
    dir = strtok(strcpy(path_copy, path), ":");
    while (dir != NULL)
    {
        directories[num_directories] = dir;
        num_directories++;
        dir = strtok(NULL, ":");
    }

    while (1)
    {
        char path_buffer[MAX_PATH_LENGTH];
        if (getcwd(cwd, MAX_PATH_LENGTH) == NULL)
        {
            fprintf(stderr, "Error obteniendo el directorio actual: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (isatty(STDIN_FILENO))
        {
            printf("%s$ ", cwd);
        }
        num_char = getline(&str, &n, stdin);
        if (num_char == -1)
        {
            free(str);
            exit(EXIT_SUCCESS);
        }
        if (num_char == 1)
        {
            /* Línea vacía */
            continue;
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
            j++;
            argv[j] = strtok(NULL, " ");
        }

        /* Handle built-in commands */
        if (strcmp(argv[0], "cd") == 0)
        {
            if (argv[1] == NULL)
            {
                /* Change to home directory */
                chdir(getenv("HOME"));
            }
            else if (chdir(argv[1]) != 0)
            {
                printf("%s: No such file or directory\n", argv[1]);
            }
            continue;
        }
        else if (strcmp(argv[0], "exit") == 0)
        {
            exit(0);
        }

        /* Check if command exists in PATH */
        found = 0;
        for (i = 0; i < num_directories; i++)
        {
            snprintf(path_buffer, MAX_PATH_LENGTH, "%s/%s", directories[i], argv[0]);
            if (access(path_buffer, X_OK) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("%s: command not found\n", argv[0]);
            continue;
        }

        /* Fork and execute command */
        pid = fork();
        if (pid == -1)
        {
            fprintf(stderr, "Error al crear un proceso hijo: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            execve(path_buffer, argv, env);
            fprintf(stderr, "Error al ejecutar el comando %s: %s\n", argv[0], strerror(errno));
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }
}