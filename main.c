#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 100

/**
 * main - main command line interface for running
 *
 * Return: void
 */
int main(void)
{
char cmd[MAX_CMD_LEN];
pid_t pid;
int status;

while (1)
{
printf("$");
fflush(stdout);

if (fgets(cmd, MAX_CMD_LEN, stdin) == NULL)
{
printf("\n");
break;
}

if (cmd[strlen(cmd) - 1] == '\n')
{
cmd[strlen(cmd) - 1] = '\0';
}

pid = fork();

if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
execlp(cmd, cmd, (char *) NULL);
perror("exec");
exit(EXIT_FAILURE);
}
else
{
do {
waitpid(pid, &status, WUNTRACED);
} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}
} return 0;
}
