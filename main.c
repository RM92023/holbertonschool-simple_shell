#include "main.h"

int main(int ac, char **av, char **env)
{
    int interactive = isatty(STDIN_FILENO);
    if (ac == 1)
    {
        prompt(av, env, interactive);
    }
    return (0);
}