#ifndef SHELL_H
#define SHELL_H

/*#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <libgen.h>
#include <limits.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

void prompt(char **av, char **env);
char *search_command(char *cmd, char **env);*/


#define TRUE 1
#define FALSE !TRUE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>

/* Shell pid, pgid, terminal modes */
static pid_t GBSH_PID;
static pid_t GBSH_PGID;
static int GBSH_IS_INTERACTIVE;
static struct termios GBSH_TMODES;

static char* currentDirectory;
extern char** environ;

struct sigaction act_child;
struct sigaction act_int;

int no_reprint_prmpt;

pid_t pid;


/**
 * SIGNAL HANDLERS
 */
 /*signal handler for SIGCHLD */
void signalHandler_child(int p);
/* signal handler for SIGINT*/
void signalHandler_int(int p);


int changeDirectory(char * args[]);

#endif
