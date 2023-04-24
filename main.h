#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/wait.h>

void prompt(char **av, char **env);
char *search_command(char *cmd, char **env);

#endif
