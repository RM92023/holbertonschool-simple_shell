#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

char *get_line(void)
{
    char *line = malloc(BUFFER_SIZE);
    if (!line)
    {
perror("Error: malloc");
exit(EXIT_FAILURE);
    }

    if (fgets(line, BUFFER_SIZE, stdin) == NULL)
    {
        perror("Error: fgets");
        exit(EXIT_FAILURE);
    }

    return line;
}

char **split_line(char *line)
{
    int bufsize = BUFFER_SIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("Error: malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " \t\n");
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += BUFFER_SIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("Error: realloc");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " \t\n");
    }

    tokens[position] = NULL;
    return tokens;
}

int execute_command(char **args)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (execvp(args[0], args) == -1)
        {
            perror("Error: execvp");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("Error: fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        do {
            pid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int main(void)
{
    char *line;
    char **args;
    int status;

    do
    {
        printf("$ ");
        line = get_line();
        args = split_line(line);
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);

    return EXIT_SUCCESS;
}
