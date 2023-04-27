# Simple Shell :dragon:

<img src="https://emojis.slackmojis.com/emojis/images/1531849353/4244/blob-octopus.gif" width="60" height="60"/> ![GitHub contributors](https://img.shields.io/github/contributors/RM92023/holbertonschool-simple_shell) ![Badge en Desarollo](https://img.shields.io/badge/STATUS-IN%20DEVELOPMENT-green) ![my badge](https://img.shields.io/badge/branch-2-blue) <img src="https://emojis.slackmojis.com/emojis/images/1531849353/4244/blob-octopus.gif" width="60" height="60"/>
***
[![GitHub watchers](https://img.shields.io/github/watchers/RM92023/holbertonschool-simple_shell.svg?style=social&label=Watch&maxAge=2592000)](https://GitHub.com/RM92023/holbertonschool-simple_shell/watchers/)
![C](https://img.shields.io/badge/-C-black?logo=c&style=social)&nbsp;&nbsp;<img src="https://media.giphy.com/media/WUlplcMpOCEmTGBtBW/giphy.gif" width="30">

![Jokes Card](https://readme-jokes.vercel.app/api)

***
## Index :earth_americas:

* [Index](#index-earth_americas)
* [Description](#description)
* [Output](#output-suspect)
* [Authorized functions](#authorized-functions)
* [Compilator](#compilator)
* [Testing](#testing)
* [Commands](#commands)
* [Files](#files)
* [Authors](#authors)
***

## Description :floppy_disk:

"Simple Shell" is a project that recreates the Shell, which incorporates a programming language that controls processes and files and starts and controls other programs. In short, the shell facilitates communication with the operating system. The shell works by means of commands entered by the user.

![](https://e1.pxfuel.com/desktop-wallpaper/391/461/desktop-wallpaper-1366x768-coding-hello-world-programming-for-laptop-notebook-codding.jpg)
***
## Output :unicorn:

Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)

Example of error with `sh`

~~~c
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
~~~

same error with `hsh`
~~~c
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
~~~

***
## Authorized functions :black_joker:

* access (man 2 access)
* chdir (man 2 chdir)
* close (man 2 close)
* closedir (man 3 closedir)
* execve (man 2 execve)
* exit (man 3 exit)
* _exit (man 2 _exit)
* fflush (man 3 fflush)
* fork (man 2 fork)
* free (man 3 free)
* getcwd (man 3 getcwd)
* getline (man 3 getline)
* getpid (man 2 getpid)
* isatty (man 3 isatty)
* kill (man 2 kill)
* malloc (man 3 malloc)
* open (man 2 open)
* opendir (man 3 opendir)
* perror (man 3 perror)
* printf (man 3 printf)
* fprintf (man 3 fprintf)
* vfprintf (man 3 vfprintf)
* sprintf (man 3 sprintf)
* putchar (man 3 putchar)
* read (man 2 read)
* readdir (man 3 readdir)
* signal (man 2 signal)
* stat (__xstat) (man 2 stat)
* lstat (__lxstat) (man 2 lstat)
* fstat (__fxstat) (man 2 fstat)
* strtok (man 3 strtok)
* wait (man 2 wait)
* waitpid (man 2 waitpid)
* wait3 (man 2 wait3)
* wait4 (man 2 wait4)
* write (man 2 write)

***
## Compilator :space_invader:

~~~c
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
~~~

To run the shell is as follows:

~~~c
./hsh
~~~
***
## Testing :performing_arts:

The shell should work like this in interactive mode:

~~~c
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
~~~

But also in non-interactive mode
~~~c
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
~~~
***
## Commands :trident:

| Commands |   Description   |
|----------|-----------------|
|cd|command that changes the current working directory to the previous working directory|
|pwd|command that writes to standard output the full path name of your current directory|
|ls|command to list the files in a long format|
|echo|command tool used for displaying lines of text or string.|
|mkdir|command creates directories|

Exit commands

|Exit|
|------|
|Ctrl-D|
|Ctrl-C|



***
## Files :crossed_swords:

* **README.md:** This file contains the information of this project

* **AUTHORS:** This file contains the author of this project

* **main.h:** This file contains prototypes and the project libraries

* **main.c:** This file is the function that is going to execute the simple shell

* **prompt.c:** This file contains all shell code

* **man_1_simple_shell:**


***
## Authors :alien:

* ![GitHub Contributors Image](https://contrib.rocks/image?repo=RM92023/holbertonschool-low_level_programming)
Robinson Muneton Jaramillo - <a href="https://github.com/RM92023" target="_blank"> @RM92023</a> ![Your Repository's Stats](https://github-readme-stats.vercel.app/api?username=RM92023&show_icons=true)



* ![GitHub Contributors Image](https://contrib.rocks/image?repo=sandro132/holbertonschool-low_level_programming) 
Miguel Angel Velez Ocampo - <a href="https://github.com/sandro132" target="_blank"> @sandro132</a>![Your Repository's Stats](https://github-readme-stats.vercel.app/api?username=sandro132&show_icons=true)
***
