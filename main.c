#include "main.h"

#define MAX_COMMAND 10

/**
 * main - main function for simple shell
 *
 * @ac: argument count
 * @av: array of arguments
 * @env: array of environment variables
 *
 * Return: 0 on success, -1 on failure
 */
int main(int ac, char **av, char **env)
{
    char *str = NULL;
    int i, j, last_cmd_exit_status = 0;
    size_t n = 0;
    ssize_t num_char;
    char *argv[MAX_COMMAND];
    char **ptr;

    while (1)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("$ ");
            fflush(stdout);
        }
        num_char = getline(&str, &n, stdin);
        if (num_char == -1)
        {
            free(str);
            return (last_cmd_exit_status);
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
        while (argv[j])
        {
            argv[++j] = strtok(NULL, " ");
        }
        if (strcmp(argv[0], "exit") == 0)
        {
            free(str);
            return (last_cmd_exit_status);
        }
        if (strcmp(argv[0], "env") == 0)
        {
            ptr = env;
            while (*ptr != NULL)
            {
                printf("%s\n", *ptr);
                ptr++;
            }
        }
        else
        {
            last_cmd_exit_status = execute_command(argv, env);
        }
    }
    return (0);
}



/*
 * main - main function
 *
 * @ac: application context
 * @av: application context
 * @env: application environment
 *
 * Return: application context
 */

/*
int main(int ac, char **av, char **env)
{
if (ac == 1)
{
prompt(av, env);
}
return (0);
}
*/