#include "main.h"

char *search_command(char *cmd, char **env)
{
    char *path = NULL;
    char *token, *cmd_path;
    int i = 0;

    while (env[i])
    {
        if (strncmp(env[i], "PATH=", 5) == 0)
        {
            path = env[i] + 5;
            break;
        }
        i++;
    }

    if (path == NULL)
        return NULL;

    token = strtok(path, ":");
    while (token != NULL)
    {
        cmd_path = malloc(strlen(token) + strlen(cmd) + 2);
        sprintf(cmd_path, "%s/%s", token, cmd);
        if (access(cmd_path, F_OK) == 0)
            return cmd_path;
        free(cmd_path);
        token = strtok(NULL, ":");
    }
    
    return NULL;
}
