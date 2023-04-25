#include "shell.h"
/**
* main - This is a "Simple" Shell project
* Return: always 0
*/

int main(void)
{
pid_t child_pid;
char *command[1024];
char *token, *line = NULL, *path_command = NULL;
size_t i, n;
int status = 0;

while (1)
{
    if (isatty(STDIN_FILENO))
        printf("($)");
    fflush(stdin);
    signal(SIGINT, continuePROM);
    if (getline(&line, &n, stdin) == EOF)
        break;
    if (*line == '\n' || *line == '\t')
        continue;
    token = strtok(line, " \t\n");
    for (i = 0; i < 1024 && token != NULL; i++)
        command[i] = token, token = strtok(NULL, " \t\n");
    command[i] = NULL;
    if (command[0] == NULL)
    continue;
    path_command = pathfinder(command[0]);
    if (builtin(command[0]) == 0)
    {
        child_pid = fork();
        if (child_pid == 0)
        {
            if (execve(path_command, command, environ))
                perror("execve"), free(line), exit(EXIT_FAILURE);
        }
        if (child_pid > 0)
            wait(&status), free(line);
    }
    line = NULL, token = NULL, command[0] = NULL;
}
free(line), free(path_command), exit(status);
}
